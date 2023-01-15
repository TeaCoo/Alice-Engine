#include "pch.h"
#include "Application.h"
#include "FileIO/ObjFileReader.h"
#include <glad/glad.h>
#include "Alice/Buffer/MeshBuffer.h"
#include "Alice/FileIO/ShaderProcessor.h"
#include "Texture/Texture.h"
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
		
		ObjFileReader obj("../asset/model/sphere.obj");
		MeshBuffer meshBuffer(obj.meshes/*, BatchType::TEXTURE*/);

		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		
		glBufferData(GL_ARRAY_BUFFER,
			meshBuffer.length_per_vertex * meshBuffer.vertexCount * sizeof(float),
			meshBuffer.vertex_buffer->positions, 
			GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, meshBuffer.length_per_vertex * sizeof(float), 0);

		glGenBuffers(1, &index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			meshBuffer.faceEdgeCount * meshBuffer.faceCount * sizeof(unsigned int),
			meshBuffer.index_buffer->index,
			GL_STATIC_DRAW);
		
		index_count = meshBuffer.faceEdgeCount * meshBuffer.faceCount;

		ShaderProcessor shaderReader("../asset/shader/default.vert","../asset/shader/default.frag");
		unsigned int shader = CreateShader(shaderReader.vert, shaderReader.frag);
		glUseProgram(shader);
		/*
		Texture texture("../asset/icon/logo/Logo_Alice_head_opaque.png");
		texture.Bind();

		int location = glGetUniformLocation(shader, "u_Texture");
		glUniform1i(location, 0);*/

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	Application::~Application()
	{
		glDeleteBuffers(1, &id);
		glDeleteBuffers(1, &index);
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
			glClearColor(0.1, 0.1, 0.1, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);


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