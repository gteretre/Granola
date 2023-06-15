#include "grlpch.h"
#include "App.h"
#include "Window.h"
#include "Granola/Core/Log.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/Event.h"
#include "Granola/Utilities/ColorUtilities.h"

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
		constexpr glm::vec3 col1 = ColorUtilities::RGBtoFloats(120, 27, 73);
		constexpr glm::vec3 col2 = ColorUtilities::RGBtoFloats(17, 76, 126);
		constexpr glm::vec3 col3 = ColorUtilities::RGBtoFloats(30, 173, 120);
		constexpr float a = 1.0f;

		m_VertexArray = VertexArray::Create();
		const float squareVericies[6 * 7] = {
			-0.5f, -0.75f, 0.0f, col1.r, col1.g, col1.b, a,
			0.5f, -0.5f, 0.0f, col2.r + 0.3f, col2.g - 0.2f, col2.b - 0.2f, a,
			0.5f, -0.5f, 0.0f, col2.r, col2.g, col2.b, a,
			0.0f, 0.75f, 0.0f, col3.r, col3.g, col3.b, a,
			0.15f, 0.15f, 0.0f, col3.r - 0.2f, col3.g, col3.b + 0.5f, a,
			-0.75f, 0.5f, 0.0f, col3.r + 0.4f, col3.g, col3.b, a
		};
		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(squareVericies, sizeof(squareVericies));
		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(squareLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		constexpr uint32_t squareIndicies[12] = {0, 1, 2, 2, 3, 0, 4, 4, 5, 1, 3, 5};

		Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(squareIndicies, std::size(squareIndicies));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)"; // prefix a_ for attribute

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 o_Color;
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				o_Color = vec4(v_Position+0.25, 1.0);
				o_Color = v_Color;
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
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
