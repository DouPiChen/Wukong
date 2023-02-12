#include "Wupch.h"

#include "OpenGLTexture.h"

#include <glad/gl.h>
#include <stb_image.h>

namespace Wukong
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        :m_Path(path)
	{
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
        unsigned char* data = stbi_load(m_Path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
        glDeleteTextures(1, &m_RendererID);
	}

	void  OpenGLTexture2D::Bind(uint32_t slot) const
	{
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}