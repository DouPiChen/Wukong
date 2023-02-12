#pragma once

#include "RendererAPI.h"

namespace Wukong
{
	class Renderer
	{
	public:
		static void Init();
		static void BeingScene();
		static void EndScene();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};
}