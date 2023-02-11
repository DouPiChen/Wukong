#include "Wupch.h"

#include "OpenGLContext.h"

namespace Wukong
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		WU_CORE_ASSERT(windowHandle, "OpenGLContext cannot get the windowHandle");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGL(glfwGetProcAddress))
		{
			WU_CORE_ASSERT(false, "Failed to initialize GLAD2");
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}