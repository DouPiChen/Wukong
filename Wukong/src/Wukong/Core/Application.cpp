#include "Wupch.h"
#include "Application.h"

#include "Wukong/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Wukong/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Wukong
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;   
        layout (location = 1) in vec3 aColor; 

        out vec3 ourColor; 

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            ourColor = aColor; 
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;  
        in vec3 ourColor;

        void main()
        {
            FragColor = vec4(ourColor, 1.0);
        }
    )";

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WU_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//WU_CORE_TRACE(e);

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
            DrawSomething();
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
		return false;
	}

	void Application::DrawSomething()
	{

        // glfw window creation
        // --------------------
        GLFWwindow* window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
        if (window == NULL)
        {
            WU_CORE_ASSERT(false, "Failed to create GLFW window");
            glfwTerminate();
        }

        OpenGLContext* context = new OpenGLContext(window);
        context->Init();
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        Ref<Shader> shader = Shader::Create("Triangle", vertexShaderSource, fragmentShaderSource);


        float vertices[] = {
            // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

        };

        m_VertexArray = VertexArray::Create();
        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aColor"}
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[] = { 0,1,2 };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);


        // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
        //glUseProgram(shaderProgram);
        shader->Bind();

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // render the triangle
            m_VertexArray->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            context->SwapBuffers();
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
	}

}