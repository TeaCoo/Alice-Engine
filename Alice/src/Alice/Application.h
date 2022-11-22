#pragma once
#include "Core.h"
#include "Alice/Window.h"
#include "Alice/Event/ApplicationEvent.h"
#include "Alice/Log.h"

namespace Alice {
	class ALICE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	// to be defined in client
	Application* CreateApplication();
}


