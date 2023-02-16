#pragma once

#include "Wukong/Core/Window.h"
#include "Wukong/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Wukong
{
	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title = "Wukong Engine";
			unsigned int Width = 800, Height = 600;
			bool VSync = true;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}


