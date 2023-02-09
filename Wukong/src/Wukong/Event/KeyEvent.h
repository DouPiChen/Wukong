#pragma once

#include "Event.h"

namespace Wukong 
{
	class KeyEvent :public Event
	{
	public:
		inline int GetKeycode() const { return m_Keycode; }

		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryKeyboard);

	protected:
		KeyEvent(int keycode) :m_Keycode(keycode) {}
		int m_Keycode;
	};

	class KeyPressedEvent :public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int keyRepeated)
			:KeyEvent(keycode), m_KeyRepeated(keyRepeated){}
		inline int GetRepeated() const { return m_KeyRepeated; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed:\n Keycode : " << m_Keycode << ", KeyRepeated : " << m_KeyRepeated;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed);

	protected:
		int m_KeyRepeated;
	};

	class KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) :KeyEvent(keycode) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased:\n Keycode : " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class KeyTypedEvent :public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) :KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped:\n Keycode : " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};

}