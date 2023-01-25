#pragma once
#include "Core.h"
#include "Alice/Window.h"
#include "Alice/Event/Event.h"
#include "Alice/Event/ApplicationEvent.h"
#include "Alice/Layer/LayerStack.h"
#include "Alice/ImGui/ImGui_Engine_Editer.h"

namespace Alice {
	class ALICE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void ImGuiBegin();
		void ImGuiEnd();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowCloased(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_framebufferID;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static Application* s_Instance;
		bool showGUI = true;

	};
	// to be defined in client
	Application* CreateApplication();
}


