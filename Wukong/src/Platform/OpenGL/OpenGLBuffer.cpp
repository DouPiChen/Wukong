#include "Wupch.h"

#include "OpenGLBuffer.h"

#include <glad/gl.h>

namespace Wukong
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}

		WU_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		WU_PROFILE_FUNCTION();
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		WU_PROFILE_FUNCTION();
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		WU_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		WU_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		WU_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		WU_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		WU_PROFILE_FUNCTION();
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		WU_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		WU_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		WU_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		WU_PROFILE_FUNCTION();
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		WU_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		WU_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		WU_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		WU_PROFILE_FUNCTION();
		WU_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "VertexBuffer has no layout");

		glBindVertexArray(m_RendererID);
		buffer->Bind();
		
		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout)
		{
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE: GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			glEnableVertexAttribArray(m_VertexBufferIndex);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buffer)
	{
		WU_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		buffer->Bind();

		m_IndexBuffer = buffer;
	}



}