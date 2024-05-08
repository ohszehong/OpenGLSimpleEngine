#pragma once

#include "DebugUtilities.h"

#include <vector>

struct VertexAttribute
{
	unsigned int index;
	unsigned int count;
	unsigned int typeId;
	unsigned int normalized;

	inline unsigned int getAttributeSizeInBytes() const
	{
		switch (typeId)
		{
		case GL_FLOAT:
			return count * sizeof(GLfloat);

		case GL_UNSIGNED_INT:
			return count * sizeof(GLuint);

		case GL_UNSIGNED_BYTE:
			return count * sizeof(GLubyte);

		default:
			ASSERT(false);
			return 0;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexAttribute> m_VertexAttributes;

	unsigned int m_Stride; //total bytes of all the vertex attributes combined

public:
	VertexBufferLayout();
	~VertexBufferLayout();

	const std::vector<VertexAttribute>& getVertexAttributes() const; 

	inline unsigned int getStride() const 
	{ 
		return m_Stride;
	}

	template <typename T>
	void PushVertexAttribute(unsigned int index, unsigned int count);
};