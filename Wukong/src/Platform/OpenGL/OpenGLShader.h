#pragma once

#include "Wukong/Renderer/Shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Wukong
{
	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind()const override;
		virtual void Unbind() const override;

        void SetBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
        }
        void SetInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
        }
        void SetFloat(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
        }
        void SetVec2(const std::string& name, const glm::vec2& value) const
        {
            glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
        }
        void SetVec2(const std::string& name, float x, float y) const
        {
            glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
        }
        void SetVec3(const std::string& name, const glm::vec3& value) const
        {
            glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
        }
        void SetVec3(const std::string& name, float x, float y, float z) const
        {
            glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
        }
        void SetVec4(const std::string& name, const glm::vec4& value) const
        {
            glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
        }
        void SetVec4(const std::string& name, float x, float y, float z, float w) const
        {
            glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
        }
        void SetMat2(const std::string& name, const glm::mat2& mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        void SetMat3(const std::string& name, const glm::mat3& mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        void SetMat4(const std::string& name, const glm::mat4& mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

		virtual const std::string& GetName() const override { return m_Name; }
		virtual const uint32_t GetRendererID() const override { return m_RendererID; }

	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}