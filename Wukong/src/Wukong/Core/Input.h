#pragma once

#include "Core.h"

namespace Wukong
{
	class Input
	{
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return s_InputInstance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) 
			{ return s_InputInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float>GetMousePosition() { return s_InputInstance->GetMousePositionImpl(); }
		inline static float GetMouseXPos() { return s_InputInstance->GetMouseXImpl(); }
		inline static float GetMouseYPos() { return s_InputInstance->GetMouseYImpl(); }

	protected:
		Input() = default;

		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float>GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Scope<Input> s_InputInstance;
	};


}