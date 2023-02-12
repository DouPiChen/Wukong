#include "Wupch.h"
#include "Application.h"

#include "Wukong/Renderer/Buffer.h"
#include "Wukong/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Wukong/Renderer/Texture.h"
#include "Wukong/Renderer/RenderCommand.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

namespace Wukong
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  
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
    

    const char* vertexShaderSource2 = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec2 aTexCoord;

        out vec3 ourColor;
        out vec2 TexCoord;

        void main()
        {
	        gl_Position = vec4(aPos, 1.0);
	        ourColor = aColor;
	        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
        }
    )";

    const char* fragmentShaderSource2 = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 ourColor;
        in vec2 TexCoord;

        // texture samplers
        uniform sampler2D texture1;
        uniform sampler2D texture2;

        void main()
        {
	        //FragColor = texture(ourTexture, TexCoord);
            //FragColor = vec4(ourColor, 1.0);
            //FragColor = texture(ourTexture, TexCoord)*vec4(ourColor,1.0);
	        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
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

        Ref<Shader> shader = Shader::Create("Triangle", vertexShaderSource, fragmentShaderSource);
        shader->Bind();
        


        float vertices2[] = {
            // positions          // colors           // texture coords
             0.7f,  0.6f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
             0.7f, -0.6f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.7f, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.7f,  0.6f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices2[] = {
            0, 1, 3,// first triangle
            1, 2, 3  // second triangle
        };

        m_VertexArray2 = VertexArray::Create();
        Ref<VertexBuffer> vertexBuffer2 = VertexBuffer::Create(vertices2, sizeof(vertices2));
        BufferLayout layout2 = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aColor"},
            {ShaderDataType::Float2, "aTexCoord"}
        };
        vertexBuffer2->SetLayout(layout2);
        m_VertexArray2->AddVertexBuffer(vertexBuffer2);

        Ref<IndexBuffer> indexBuffer2 = IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t));
        m_VertexArray2->SetIndexBuffer(indexBuffer2);

        std::string filepath2a = "assets/textures/container.jpg";
        Ref<Texture2D> texture2a = Texture2D::Create(filepath2a);
        std::string filepath2b = "assets/textures/awesomeface.jpg";
        Ref<Texture2D> texture2b = Texture2D::Create(filepath2b);


        Ref<Shader> shader2 = Shader::Create("Rectangle", vertexShaderSource2, fragmentShaderSource2);
        shader2->Bind();

        m_VertexArray->Unbind();
        m_VertexArray2->Unbind();

        std::dynamic_pointer_cast<OpenGLShader>(shader2)->SetInt("texture1", 0);
        std::dynamic_pointer_cast<OpenGLShader>(shader2)->SetInt("texture2", 1);
   

        while (!glfwWindowShouldClose(window))
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            /*
            shader->Bind();           
            m_VertexArray->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            RenderCommand::DrawIndexed(m_VertexArray);
            m_VertexArray->Unbind();
            */

            shader2->Bind();
            m_VertexArray2->Bind();
            texture2a->Bind(0);
            texture2b->Bind(1);
            RenderCommand::DrawIndexed(m_VertexArray2);
            m_VertexArray2->Unbind();

            context->SwapBuffers();

            glfwPollEvents();
        }

        glfwTerminate();
	}

}