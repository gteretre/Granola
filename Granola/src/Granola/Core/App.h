#pragma once
#include "Base.h"
#include "Window.h"
#include "Granola/Core/LayerStack.h"
#include "Granola/Core/Timestep.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/Event.h"
#include "Granola/ImGui/ImGuiLayer.h"

namespace Granola
{
	class App
	{
	public:
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event &currentEvent);
		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		static App &Get() { return *s_Instance; }
		[[nodiscard]] Window &GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(const WindowCloseEvent &currentEvent);
		bool OnWindowResize(const WindowResizeEvent &currentEvent);


		Scope<Window> m_Window;
		static App *s_Instance;
		ImGuiLayer *m_ImGuiLayer;

		LayerStack m_LayerStack{};
		float m_LastFrameTime = 0.0f;
		bool m_IsRunning = true;
		bool m_Minimized = false;
	};

	// To be defined in client
	App *CreateApp();
}
