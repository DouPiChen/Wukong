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

        virtual void SetBool(const std::string& name, bool value) const override;
        virtual void SetInt(const std::string& name, int value) const override;
        virtual void SetIntArray(const std::string& name, int* value, uint32_t count) const override;
        virtual void SetFloat(const std::string& name, float value) const override;
        virtual void SetVec2(const std::string& name, const glm::vec2& value) const override;
        virtual void SetVec2(const std::string& name, float x, float y) const override;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) const override;
        virtual void SetVec3(const std::string& name, float x, float y, float z) const override;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) const override;
        virtual void SetVec4(const std::string& name, float x, float y, float z, float w) const override;
        virtual void SetMat2(const std::string& name, const glm::mat2& mat) const override;
        virtual void SetMat3(const std::string& name, const glm::mat3& mat) const override;
        virtual void SetMat4(const std::string& name, const glm::mat4& mat) const override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		void Compile(const std::unordered_map<unsigned int, std::string>& shaderSrc);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}