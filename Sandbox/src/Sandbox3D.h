#pragma once

#include <Wukong.h>

class Sandbox3D : public Wukong::Application
{
public:
	Sandbox3D();
	~Sandbox3D();
	virtual void Run() override;
	void OnEvent(Wukong::Event& e);

private: 
	Wukong::Ref<Wukong::VertexArray> m_VertexArray;
	Wukong::Ref<Wukong::Shader> m_Shader;
	Wukong::Ref<Wukong::Texture2D> m_Texture1, m_Texture2;
	//Wukong::PrespectiveCamera m_Camera;
	Wukong::OrthographicCamera m_Camera;
};