#pragma once

#include <Wukong.h>

class Sandbox2DLayer : public Wukong::Layer
{
public:
	Sandbox2DLayer();
	virtual ~Sandbox2DLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Wukong::TimeStep ts) override;
	virtual void OnImGuiRender() override {}
	virtual void OnEvent(Wukong::Event& e) override;

private:
	Wukong::Ref<Wukong::Texture2D> m_CheckerboardTexture;
	Wukong::OrthographicCamera m_Camera;
	Wukong::Ref<Wukong::VertexArray> m_VertexArray;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox2D :public Wukong::Application
{
public:
	Sandbox2D()
	{
		PushLayer(new Sandbox2DLayer());
	}

	~Sandbox2D() {}
};