#pragma once

#include "Core.h"

namespace Wukong
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
	};

	Application* CreateApplication();
}