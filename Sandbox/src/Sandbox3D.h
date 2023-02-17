#pragma once

#include <Wukong.h>

class Sandbox3DLayer : public Wukong::Layer
{
public:
	Sandbox3DLayer();
	virtual ~Sandbox3DLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Wukong::TimeStep ts) override;
	virtual void OnImGuiRender() override {}
	virtual void OnEvent(Wukong::Event& e) override;

private: 
	Wukong::Ref<Wukong::VertexArray> m_VertexArray;
	Wukong::Ref<Wukong::Shader> m_Shader;
	Wukong::Ref<Wukong::Texture2D> m_Texture1, m_Texture2;
	Wukong::PrespectiveCamera m_Camera;
	//Wukong::OrthographicCamera m_Camera;
};

class Sandbox3D :public Wukong::Application
{
public:
	Sandbox3D()
	{
		PushLayer(new Sandbox3DLayer());
	}

	~Sandbox3D() {}
};