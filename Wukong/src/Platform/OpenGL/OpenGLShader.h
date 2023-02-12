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

		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}