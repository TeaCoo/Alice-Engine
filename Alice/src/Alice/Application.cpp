#include "pch.h"
#include "Application.h"
#include "FileIO/ObjFileReader.h"
#include <glad/glad.h>

namespace Alice {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		ALICE_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		if (showGUI) 
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
		
		unsigned int id;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		const float position[6] = {
			-0.5, -0.5,
			 0.0,  0.5,
			 0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), position, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2*sizeof(float), 0);

		ObjFileReader obj("../asset/model/cube.obj");
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloased));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	bool Application::OnWindowCloased(WindowCloseEvent& event) 
	{
		m_Running = false;
		return true;
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			
			glDrawArrays(GL_TRIANGLES,0,3);

			

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			if (showGUI) 
			{
				m_ImGuiLayer->Begin();

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();

				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();

		}
	}
}