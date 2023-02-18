#include "Wupch.h"

#include "OpenGLTexture.h"

#include <glad/gl.h>
#include <stb_image.h>

namespace Wukong
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
    {
        WU_PROFILE_FUNCTION();
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            WU_CORE_ASSERT(false, "Failed to load texture");
        }
    }

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        :m_Path(path)
	{
        WU_PROFILE_FUNCTION();
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID); 
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = nullptr;
        {
            WU_PROFILE_SCOPE("stbi_load - Load OpenGL Texture");
            data = stbi_load(m_Path.c_str(), &width, &height, &nrChannels, 0);
        }

        GLenum dataFormat = 0;
        if (nrChannels == 4)
        {
            dataFormat = GL_RGBA;
        }
        else if (nrChannels == 3)
        {
            dataFormat = GL_RGB;
        }
        else
        {
            WU_CORE_ASSERT(false, "Texture Format not supported");
        }
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            WU_CORE_ASSERT(false, "Failed to load texture");
        }
        stbi_image_free(data);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
        WU_PROFILE_FUNCTION();
        glDeleteTextures(1, &m_RendererID);
	}

	void  OpenGLTexture2D::Bind(uint32_t slot) const
	{
        WU_PROFILE_FUNCTION();
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}