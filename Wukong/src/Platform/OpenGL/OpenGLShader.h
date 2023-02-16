#pragma once

#include "Wukong/Renderer/Shader.h"


#include <glm/glm.hpp>

namespace Wukong
{
	class OpenGLShader :public Shader
	{
	public:
        OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~OpenGLShader();

		virtual void Bind()const override;
		virtual void Unbind() const override;

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec2(const std::string& name, float x, float y) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;
        void SetMat2(const std::string& name, const glm::mat2& mat) const;
        void SetMat3(const std::string& name, const glm::mat3& mat) const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		void Compile(const std::unordered_map<unsigned int, std::string>& shaderSrc);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}