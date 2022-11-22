#pragma once
#include "Core.h"
#include "Alice/Window.h"
#include "Alice/Event/Event.h"
#include "Alice/Event/ApplicationEvent.h"
#include "Alice/Layer/LayerStack.h"

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
	private:
		bool OnWindowCloased(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	// to be defined in client
	Application* CreateApplication();
}


