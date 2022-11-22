#include "pch.h"
#include "Application.h"
#include "Alice/Event/ApplicationEvent.h"
#include "Alice/Log.h"
namespace Alice {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent e(200, 100);
		ALICE_TRACE(e);
		while (true);
	}
}