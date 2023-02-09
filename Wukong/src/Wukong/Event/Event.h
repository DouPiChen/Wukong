#pragma once
#include "Wupch.h"

#include "Wukong/Core/Core.h"

#define EVENT_CLASS_TYPE(type)\
	static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_GET_CATEGORY(category) virtual int GetCategoryFlag() const override { return category; }

namespace Wukong
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	class Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlag() const = 0;
		virtual std::string ToString() const { return GetName(); }
		inline bool IsInCategory(EventCategory type)
		{
			return GetCategoryFlag() & type;
		}
		bool IsHandled() { return m_Handled; }
		void MarkHandled() { m_Handled = true; }

		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) :m_Event(e) {}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}


	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
