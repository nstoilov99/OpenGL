#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& filePath)
	: m_FilePath(filePath), m_RenderID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_RenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	Unbind();
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
		// Free the local buffer after uploading to GPU
		// This is important to avoid memory leaks
		// and to ensure that the texture data is stored in GPU memory
		// instead of CPU memory.
		// The local buffer is no longer needed after this point.
		// It can be freed to save memory.

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RenderID));
	// Delete the texture from GPU memory
	// This is important to avoid memory leaks
	// and to ensure that the texture data is no longer stored in GPU memory
	// after the texture object is destroyed.
	// The texture object is no longer needed after this point.
	// It can be deleted to save memory.
}

void Texture::Bind(unsigned int slot /* = 0 */) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
