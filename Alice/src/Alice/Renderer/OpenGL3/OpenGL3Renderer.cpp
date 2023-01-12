#include "pch.h"
#include "Alice/Renderer/OpenGL3/OpenGL3Renderer.h"


namespace Alice
{
	OpenGL3Renderer::OpenGL3Renderer(int width, int height, const char* title) 
		:Width(width), Height(height), Title(title)
	{
		setRenderPlatform(RendererType::OpenGL3);
	}

	OpenGL3Renderer::~OpenGL3Renderer()
	{
	}

	void OpenGL3Renderer::Init()
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ALICE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ALICE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGL3Renderer::SetSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		SetIsSync(enabled);
	}

	void OpenGL3Renderer::Shudown()
	{
		glfwDestroyWindow(m_Window);
	}
}
