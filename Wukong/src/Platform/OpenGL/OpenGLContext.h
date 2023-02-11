#pragma once

#include "Wukong/Renderer/GraphicsContext.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Wukong
{
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}