#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Granola/LayerStack.h"
#include "Granola/ImGui/ImGuiLayer.h"

#include "Granola/Renderer/Buffer.h" // TODO remporary
#include "Granola/Renderer/Shader.h" // TODO remporary

namespace Granola
{
	class App
	{
	public:
		App();
		virtual ~App();

		void Run() const;
		void OnEvent(Event &currentEvent);
		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		static App &Get() { return *s_Instance; }
		[[nodiscard]] Window &GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent &currentEvent);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer *m_ImGuiLayer; //std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack{};
		static App *s_Instance;

		unsigned int m_VertexArray{};

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	// To be defined in client
	App *CreateApp();
}
