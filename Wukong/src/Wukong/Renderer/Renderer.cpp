#include "Wupch.h"

#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

namespace Wukong
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::BeingScene(Camera& camera)
	{
		s_SceneData->ViewMatrix = camera.GetViewMatrix();
		s_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}