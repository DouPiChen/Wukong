#pragma once

#include "Core.h"

#include "Layer.h"
#include "Wukong/Event/Event.h"
#include "Wukong/Event/ApplicationEvent.h"
#include "Wukong/Core/Window.h"

#include "Wukong/Renderer/Camera.h"
#include "Wukong/Renderer/Buffer.h"
#include "Wukong/Renderer/Shader.h"
#include "Wukong/Renderer/Texture.h"

namespace Wukong
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	protected:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}