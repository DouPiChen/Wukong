#pragma once

#include "Wukong/Renderer/Texture.h"

namespace Wukong
{
	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, void* data);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void  Bind(uint32_t slot = 0) const override;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}