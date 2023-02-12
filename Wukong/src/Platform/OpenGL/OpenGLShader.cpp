#include "Wupch.h"

#include "OpenGLShader.h"

#include <glad/gl.h>

namespace Wukong
{
	OpenGLShader::OpenGLShader(const std::string& name,
		const std::string& vertexSrc,
		const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

    void OpenGLShader::SetBool(const std::string& name, bool value)
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }
	
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrc)
	{
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
}