#include "Wupch.h"

#include "OpenGLShader.h"

#include <glad/gl.h>

namespace Wukong
{

    OpenGLShader::OpenGLShader(const std::string& name, 
        const std::string& vertexPath,
        const std::string& fragmentPath)
    {
        WU_PROFILE_FUNCTION();
        std::string vertexSrc;
        std::string fragmentSrc;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath.c_str());
            fShaderFile.open(fragmentPath.c_str());
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexSrc = vShaderStream.str();
            fragmentSrc = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);

    }

	OpenGLShader::~OpenGLShader()
	{
        WU_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
        WU_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
        WU_PROFILE_FUNCTION();
		glUseProgram(0);
	}

 
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrc)
	{
        WU_PROFILE_FUNCTION();
        const char* vertexShaderSource = shaderSrc.at(GL_VERTEX_SHADER).c_str();
        const char* fragmentShaderSource = shaderSrc.at(GL_FRAGMENT_SHADER).c_str();
        
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            WU_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{0}", infoLog);
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            WU_CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{0}", infoLog);
        }
        // link shaders
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            WU_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        m_RendererID = shaderProgram;
	}

    void OpenGLShader::SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
    }
    void OpenGLShader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }
    void OpenGLShader::SetIntArray(const std::string& name, int* value, uint32_t count) const
    {
        glUniform1iv(glGetUniformLocation(m_RendererID, name.c_str()), count, value);
    }
    void OpenGLShader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }
    void OpenGLShader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::SetVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
    }
    void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
    }
    void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
    }
    void OpenGLShader::SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}