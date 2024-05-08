#pragma once

#include "DebugUtilities.h"
#include <string>

class Texture
{
private:
	unsigned int m_TextureId; 
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	unsigned int slot;

public:
	//for any image 
	Texture(const std::string& path, unsigned int slot = 0);

	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void BindOnly();
	void ActiveOnly(unsigned int slot = 0) const;

	inline int GetWidth() const
	{
		return m_Width;
	}

	inline int GetHeight() const
	{
		return m_Height;
	}

	inline unsigned int GetTextureId() const
	{
		return m_TextureId;
	}

	unsigned char* GetBuffer();

};