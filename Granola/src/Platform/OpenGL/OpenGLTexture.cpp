#include "grlpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Granola
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		const stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		GRL_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;


		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		GRL_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		// create and bind texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, static_cast<int>(m_Width), static_cast<int>(m_Height));

		// if texture is too big, it will be scaled down, if it is too small, it will be scaled up
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// upload texture data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, static_cast<int>(m_Width), static_cast<int>(m_Height),
							dataFormat,GL_UNSIGNED_BYTE, data);

		stbi_image_free(const_cast<stbi_uc*>(data));
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(const uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
