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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Wukong
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec2 aTexCoord;

        out vec3 ourColor;
        out vec2 TexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
	        //gl_Position = vec4(aPos, 1.0);
            gl_Position = projection * view * model * vec4(aPos, 1.0);
	        ourColor = aColor;
	        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
        }
    )";

    const char* fragmentShaderSource = R"(
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
            //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor,1.0);
	        //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
            FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourColor,1.0);
        }
    )";


    // camera
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;	
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float cameraSpeed = static_cast<float>(2.5 * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }

 
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }

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
        RenderCommand::Init();
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glEnable(GL_DEPTH_TEST);

        float vertices[] = {
            // positions          // colors           // texture coords
           - 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,     1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,     0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,     1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,       0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,       1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,       1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,       0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,       1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,       1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,       0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,       0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 3,// first triangle
            1, 2, 3  // second triangle
        };
        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        m_VertexArray = VertexArray::Create();
        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            {ShaderDataType::Float3, "aPos"},
            {ShaderDataType::Float3, "aColor"},
            {ShaderDataType::Float2, "aTexCoord"}
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        /*
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        */

        std::string filepath1 = "assets/textures/container.jpg";
        Ref<Texture2D> texture1 = Texture2D::Create(filepath1);
        std::string filepath2 = "assets/textures/awesomeface.jpg";
        Ref<Texture2D> texture2 = Texture2D::Create(filepath2);

        Ref<Shader> shader = Shader::Create("Rectangle", vertexShaderSource, fragmentShaderSource);
        shader->Bind();

        m_VertexArray->Unbind();

        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetInt("texture1", 0);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetInt("texture2", 1);
   

        while (!glfwWindowShouldClose(window))
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window);
          
            glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
            std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("projection", projection);
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("view", view);
            
         
            shader->Bind();
            m_VertexArray->Bind();
            texture1->Bind(0);
            texture2->Bind(1);



            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            //RenderCommand::DrawIndexed(m_VertexArray);
            m_VertexArray->Unbind();

            context->SwapBuffers();

            glfwPollEvents();
        }

        glfwTerminate();
	}

}