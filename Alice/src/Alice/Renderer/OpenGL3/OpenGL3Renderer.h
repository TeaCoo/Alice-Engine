#pragma once
#include "Alice/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Alice
{
	static bool s_GLFWInitialized = false;
	class OpenGL3Renderer : Renderer
	{
	public:
		OpenGL3Renderer(int width, int height, const char* title);
		~OpenGL3Renderer();
		void Init() override;
		void SetSync(bool enabled) override;
		void Shudown() override;
	private:
		int Width;
		int Height;
		const char* Title;

	};
}

