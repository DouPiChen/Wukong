#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

	{
		WU_PROFILE_SCOPE("Renderer Prepare");
		Wukong::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		Wukong::RenderCommand::Clear();
	}

	{
		WU_PROFILE_SCOPE("Renderer Draw");
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		Wukong::Renderer2D::BeginScene(m_Camera);
		Wukong::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f }, { 0.5f, 0.5f }, -60.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Wukong::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Wukong::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Wukong::Renderer2D::DrawQuad({ -0.5f, 0.5f }, { 0.75f, 0.4f }, m_SquareColor);
		Wukong::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Wukong::Renderer2D::DrawRotatedQuad({ -2.0f, 2.0f, 0.0f }, { 2.0f, 2.0f }, rotation,  m_CheckerboardTexture, 8.0f);
		Wukong::Renderer2D::EndScene();
	}

}

void Sandbox2DLayer::OnEvent(Wukong::Event& e)
{
	m_Camera.OnEvent(e);
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}