#include "Sandbox3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float vertices[] = {
    // positions          // colors           // texture coords
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,     0.0f, 0.0f,
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
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35
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

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Sandbox3DLayer::Sandbox3DLayer()
    :Layer("Sandbox3DLayer")
{
}

Sandbox3DLayer::~Sandbox3DLayer()
{}

void Sandbox3DLayer::OnAttach()
{
    auto& window = Wukong::Application::Get().GetWindow();
    float width = (float)(window.GetWidth());
    float height = (float)(window.GetHeight());
    m_Camera = Wukong::PrespectiveCamera(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f, width, height);

    m_VertexArray = Wukong::VertexArray::Create();
    Wukong::Ref<Wukong::VertexBuffer> vertexBuffer = Wukong::VertexBuffer::Create(vertices, sizeof(vertices));
    Wukong::BufferLayout layout = {
        {Wukong::ShaderDataType::Float3, "a_Position"},
        {Wukong::ShaderDataType::Float3, "a_Color"},
        {Wukong::ShaderDataType::Float2, "a_TexCoord"}
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    Wukong::Ref<Wukong::IndexBuffer> indexBuffer = Wukong::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_Texture1 = Wukong::Texture2D::Create("assets/textures/container.jpg");
    m_Texture2 = Wukong::Texture2D::Create("assets/textures/awesomeface.png");

    m_Shader = Wukong::Shader::Create("Boxes", "assets/shaders/boxes.vs", "assets/shaders/boxes.fs");

    m_Shader->Bind();
    m_Shader->SetInt("u_Texture1", 0);
    m_Shader->SetInt("u_Texture2", 1);
    m_VertexArray->Bind();
    m_Texture1->Bind(0);
    m_Texture2->Bind(1);
}

void Sandbox3DLayer::OnDetach()
{}

void Sandbox3DLayer::OnEvent(Wukong::Event& e)
{
    m_Camera.OnEvent(e);
}

void Sandbox3DLayer::OnUpdate(Wukong::TimeStep ts)
{
    m_Camera.OnUpdate(ts);

    Wukong::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
    Wukong::RenderCommand::Clear();

    Wukong::Renderer::BeingScene(m_Camera);

    glm::mat4 projection = m_Camera.GetProjectionMatrix();
    m_Shader->SetMat4("u_Projection", projection);
    glm::mat4 view = m_Camera.GetViewMatrix();
    m_Shader->SetMat4("u_View", view);

    m_Shader->Bind();
    m_VertexArray->Bind();
    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_Shader->SetMat4("u_Model", model);

        Wukong::Renderer::Submit(m_Shader, m_VertexArray);
    }

    Wukong::Renderer::EndScene();
}
