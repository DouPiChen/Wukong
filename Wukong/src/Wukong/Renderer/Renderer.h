#pragma once

#include "RendererAPI.h"
#include "Camera.h"
#include "Shader.h"
#include "Buffer.h"


namespace Wukong
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeingScene(Camera& camera);
		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
		};
		static Scope<SceneData> s_SceneData;
	};
}