#include "Wupch.h"

#include "OpenGLContext.h"

namespace Wukong
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		WU_PROFILE_FUNCTION();
		WU_CORE_ASSERT(windowHandle, "OpenGLContext cannot get the windowHandle");
	}

	void OpenGLContext::Init()
	{
		WU_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		
		if (!gladLoadGL(glfwGetProcAddress))
		{
			WU_CORE_ASSERT(false, "Failed to initialize GLAD2");
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		WU_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}