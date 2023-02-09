#pragma once

extern Wukong::Application* Wukong::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Wukong::CreateApplication();
	app->Run();
	delete app;
}

