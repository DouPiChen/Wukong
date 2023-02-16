#include "Wupch.h"

#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Wukong
{
	Ref<Shader> Shader::Create(const std::string& name,
		const std::string& vertexPath,
		const std::string& fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				WU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexPath, fragmentPath);
		}
		WU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}