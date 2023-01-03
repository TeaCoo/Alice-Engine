#pragma once
#include <string>
#include <GLFW/glfw3.h>
namespace Alice
{
	enum class RendererType
	{
		OpenGL3,
		Vulkan,
	};

	class Renderer
	{
	public:
		void setRenderPlatform(RendererType platform) { platformType = platform; }
		RendererType getRenderPlatform() { return platformType; }
		GLFWwindow* getWindow() { return m_Window; }
		void SetIsSync(bool enabled) { isSync = enabled; }
		bool IsSync() { return isSync; }
		virtual void Init() {}
		virtual void SetSync(bool enabled) {}
		virtual void Shudown() {}
	protected:
		GLFWwindow* m_Window;
	private:
		RendererType platformType;
		bool isSync;
	};

	static void GLFWErrorCallback(int error, const char* description)
	{
		ALICE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
}


