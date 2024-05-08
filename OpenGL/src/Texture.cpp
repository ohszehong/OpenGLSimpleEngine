#include "Texture.h"
#include "stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path, unsigned int slot) : m_TextureId(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), slot(slot)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP,4);

	std::cout << "m_BPP: " << m_BPP << std::endl;
	std::cout << "m_Width: " << m_Width << std::endl;
	std::cout << "m_Height: " << m_Height << std::endl;

	GLCall(glGenTextures(1, &m_TextureId));
	std::cout << "Texture ID: " << m_TextureId << std::endl;
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

	//Unbind();

	if (m_LocalBuffer) //if it does contains data 
		stbi_image_free(m_LocalBuffer); //clear it
}

Texture::~Texture()
{
	std::cout << "TEXTURE DELETED!" << std::endl;
	GLCall(glDeleteTextures(1, &m_TextureId));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); //this is like selecting a slot, default is 0 if this method is not used
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
}

void Texture::BindOnly()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
}

void Texture::ActiveOnly(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
}

unsigned char* Texture::GetBuffer()
{
	return m_LocalBuffer;
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
