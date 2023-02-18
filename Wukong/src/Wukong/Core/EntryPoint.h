#pragma once


extern Wukong::Application* Wukong::CreateApplication();

int main(int argc, char** argv)
{
	Wukong::Log::Init();
	WU_CORE_INFO("Wukong Engine initialize Log");
	WU_INFO("Welcome to Wukong Sandbox");

	WU_PROFILE_BEGIN_SESSION("Startup", "WukongProfile-Startup.json");
	auto app = Wukong::CreateApplication();
	WU_PROFILE_END_SESSION();

	WU_PROFILE_BEGIN_SESSION("Runtime", "WukongProfile-Runtime.json");
	app->Run();
	WU_PROFILE_END_SESSION();

	WU_PROFILE_BEGIN_SESSION("Shutdown", "WukongProfile-Shutdown.json");
	delete app;
	WU_PROFILE_END_SESSION();
}

