#pragma once

#include "Core.h"
#include "Wukong/Event/Event.h"
#include "Wukong/Event/ApplicationEvent.h"
#include "Wukong/Core/Window.h"

#include "Wukong/Renderer/Buffer.h"

namespace Wukong
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);
		void DrawSomething();

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;

		Ref<VertexArray> m_VertexArray;
	};

	Application* CreateApplication();
}