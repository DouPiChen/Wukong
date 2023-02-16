#include "Wupch.h"

#include "Application.h"
#include "Core.h"

#include "Wukong/Renderer/Buffer.h"
#include "Wukong/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Wukong/Renderer/Texture.h"
#include "Wukong/Renderer/RenderCommand.h"
#include "Wukong/Renderer/Renderer.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Wukong
{
    Application* Application::s_Instance = nullptr;
 

	Application::Application()
	{
		WU_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		//WU_CORE_TRACE(e);
	}

	void Application::Run()
	{
		WU_CORE_INFO("Wukong Engine Run");
		while (m_Running)
		{
			m_Window->OnUpdate();
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}



}