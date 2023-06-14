#include "grlpch.h"
#include "App.h"
#include "Input.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Granola/Log.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Granola
{
	App *App::s_Instance = nullptr;

	App::App() : m_ImGuiLayer(new ImGuiLayer()) // may be better to use unique_ptr in the future
	{
		//---Create App-----------------------------------
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GRL_BIND_EVENT_FN(OnEvent));
		PushOverlay(m_ImGuiLayer);


		//---Rendering-------------------------------------
		glCreateVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// anti-clockwise
		constexpr float verticies[3 * 3] = {
			-0.5f, -0.5f, 0.0f, // bottom left
			0.5f, -0.5f, 0.0f, // bottom right
			0.0f, 0.5f, 0.0f // top
		};

		m_VertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		m_VertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		constexpr uint32_t indicies[3] = {0, 1, 2};
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, std::size(indicies)));
		m_IndexBuffer->Bind();

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)"; // prefix a_ for attribute

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			
			void main()
			{
				o_Color = vec4(v_Position+0.25, 1.0);
			}
		)"; // prefix o_ for output

		m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
	}

	App::~App() = default;

	void App::PushLayer(Layer *layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer *overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void App::OnEvent(Event &currentEvent)
	{
		GRL_CORE_TRACE("{0}", currentEvent);
		EventDispatcher dispatcher(currentEvent);
		dispatcher.Dispatch<WindowCloseEvent>(GRL_BIND_EVENT_FN(OnWindowClose));

		// TODO dispatcher.Dispatch<WindowResizeEvent>(GRL_BIND_EVENT_FN(OnWindowResize));

		for (const auto &it : std::ranges::reverse_view(m_LayerStack))
		{
			if (currentEvent.IsHandled())
				break;
			it->OnEvent(currentEvent);
		}
	}

	void App::Run() const
	{
		GRL_CORE_INFO("Starting Granola Engine");
		std::vector<float> rgba = {0.1f, 0.3f, 0.0f, 1.0f};
		bool isBlue = false;
		while (m_IsRunning)
		{
			//---Just for fun--------------------------------------
			if (rgba[2] > 0.35f)
				isBlue = true;
			else if (rgba[2] < 0.05f)
				isBlue = false;
			if (!isBlue)
				rgba[2] += 0.001f;
			else
				rgba[2] -= 0.001f;
			//------------------------------------------------------


			//---OpenGL Layer---------------------------------------
			glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind(); // as first step but don't need to be here

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			if (const GLenum error = glGetError(); error != GL_NO_ERROR)
				GRL_CORE_ERROR("OpenGL Error: {0}", error);

			for (const auto layer : m_LayerStack)
				layer->OnUpdate();
			//------------------------------------------------------


			//---ImGui Layer----------------------------------------
			ImGuiLayer::Begin();
			for (const auto layer : m_LayerStack)
				layer->OnImGuiRender();
			ImGuiLayer::End();
			//------------------------------------------------------

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose([[maybe_unused]] WindowCloseEvent &currentEvent)
	{
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); // to hunt memory leaks
		_CrtDumpMemoryLeaks(); // to hunt memory leaks
		m_IsRunning = false;
		return true;
	}
}
