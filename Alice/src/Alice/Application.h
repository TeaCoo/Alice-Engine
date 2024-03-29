#pragma once
#include "Core.h"
#include "Alice/Window.h"
#include "Alice/Event/Event.h"
#include "Alice/Event/ApplicationEvent.h"
#include "Alice/Layer/LayerStack.h"
#include "Alice/ImGui/ImGuiLayer.h"

namespace Alice {
	class ALICE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowCloased(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};
	// to be defined in client
	Application* CreateApplication();
}


