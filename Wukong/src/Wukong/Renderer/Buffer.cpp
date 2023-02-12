#include "Wupch.h"

#include "Renderer.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Wukong
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch(Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				WU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		WU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				WU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, size);
		}
		WU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
		
	}

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				WU_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexArray>();
		}
		WU_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;		
	}
}