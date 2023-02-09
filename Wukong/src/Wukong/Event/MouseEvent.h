#pragma once

#include "Event.h"

namespace Wukong
{
	class MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(float xPos, float yPos)
			:m_XPos(xPos), m_YPos(yPos) {}
		inline float GetXPos() const { return m_XPos; }
		inline float GetYPos() const { return m_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved: xPos : " << GetXPos() << ", yPos : " << GetYPos();
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouse);

	private:
		float m_XPos, m_YPos;
	};

	class MouseButtonEvent :public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton);

	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};

	class MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

	class MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled: xOffset : " << GetXOffset() << ", yOffset : " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton);

	private:
		float m_XOffset, m_YOffset;
	};

}