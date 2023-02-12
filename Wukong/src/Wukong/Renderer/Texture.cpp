#include "Wupch.h"

#include "Renderer.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Wukong
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				WU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(path);
		}
		WU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;	
	}
}