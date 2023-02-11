#include "Wupch.h"

#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Wukong
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

	Ref<VertexArray> VertexArray::Create()
	{
		return CreateRef<OpenGLVertexArray>();
	}
}