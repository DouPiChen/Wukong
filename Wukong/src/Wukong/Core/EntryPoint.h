#pragma once


extern Wukong::Application* Wukong::CreateApplication();

int main(int argc, char** argv)
{
	Wukong::Log::Init();
	WU_CORE_INFO("Wukong Engine initialize Log");
	WU_INFO("Welcome to Wukong Sandbox");

	auto app = Wukong::CreateApplication();
	app->Run();
	delete app;
}

