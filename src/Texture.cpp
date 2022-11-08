#include <GL/glew.h>
#include <stb_image.h>

#include "Texture.h"
#include "GLErrorHandle.h"

Texture::Texture(const std::string filePath, /*Added for relability*/ bool freeTexData) :
	m_RendererID(0), m_FilePath(filePath),
	m_Width(0), m_Height(0), m_BPP(0), 
	m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID)); 

	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // Resampling for a minification filter.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // Resampling for a magification filter.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // Setting Wrap mode for horizontal to be clamped to the edge.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // Setting Wrap mode for vertical to be clamped to the edge.

	//Sending the image to OpenGL
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

	Unbind();

	if (m_LocalBuffer && freeTexData) 
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}

	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
