#pragma once

#include "Wukong/Renderer/Shader.h"

#include <glad/gl.h>

namespace Wukong
{
	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind()const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}