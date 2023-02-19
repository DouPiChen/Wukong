#pragma once

#include "Wukong/Renderer/Buffer.h"

namespace Wukong
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind()const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		static Ref<VertexArray> Create();

	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}