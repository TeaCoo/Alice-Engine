#pragma once
#include "Core.h"
namespace Alice {
	class ALICE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	// to be defined in client
	Application* CreateApplication();
}


