#include <Wukong.h>

class Sandbox : public Wukong::Application
{
public:
	Sandbox() {}
	~Sandbox() {}

};

Wukong::Application* Wukong::CreateApplication()
{
	return new Sandbox();
}