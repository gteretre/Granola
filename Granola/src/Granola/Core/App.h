#pragma once
#include "Base.h"
#include "Window.h"
#include "Granola/Core/LayerStack.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/Event.h"
#include "Granola/ImGui/ImGuiLayer.h"
#include "Granola/Renderer/Shader.h"
#include "Granola/Renderer/VertexArray.h"

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

		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
	};

	// To be defined in client
	App *CreateApp();
}
