#include "Sandbox2D.h"


Sandbox2DLayer::Sandbox2DLayer()
	:Layer("Sandbox2DLayer")
{

}

Sandbox2DLayer::~Sandbox2DLayer()
{}

void Sandbox2DLayer::OnAttach()
{
	auto& window = Wukong::Application::Get().GetWindow();
	float width = (float)(window.GetWidth());
	float height =  (float)(window.GetHeight());
	float ratio = width / height;
	m_Camera = Wukong::OrthographicCamera(-ratio*1.0f, ratio * 1.0f, -1.0f, 1.0f, width, height);
	m_CheckerboardTexture = Wukong::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Wukong::TimeStep ts)
{
	m_Camera.OnUpdate(ts);

	Wukong::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
	Wukong::RenderCommand::Clear();

	Wukong::Renderer2D::BeginScene(m_Camera);
	Wukong::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Wukong::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Wukong::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Wukong::Renderer2D::EndScene();
	

}

void Sandbox2DLayer::OnEvent(Wukong::Event& e)
{
	m_Camera.OnEvent(e);
}