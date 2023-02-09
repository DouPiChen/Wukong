#pragma once

#include "Event.h"

namespace Wukong
{
	class AppTickEvent :public Event
	{
	public:
		AppTickEvent() = default;
		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication);
	};

	class AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() = default;
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication);
	};

	class AppRenderEvent:public Event
	{
	public:
		AppRenderEvent() = default;
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication);
	};

	class WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() = default;
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Close";
			return ss.str();
		}
	};

	class WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			:m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize: width = " << m_Width << ", height = " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication);

	protected:
		int m_Width, m_Height;
	};
}