#pragma once

#include "Wukong/Core/Layer.h"
#include "Wukong/Event/Event.h"

namespace Wukong
{
	class ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer()
			:Layer("ImGuiLayer") {}
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void Draw();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}