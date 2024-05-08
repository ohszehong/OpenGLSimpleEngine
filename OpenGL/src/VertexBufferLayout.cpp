#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : m_Stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout()
{

}

const std::vector<VertexAttribute>& VertexBufferLayout::getVertexAttributes() const
{
	return m_VertexAttributes;
}

template <typename T>
inline void VertexBufferLayout::PushVertexAttribute(unsigned int index, unsigned int count)
{
	ASSERT(false);
}

template <>
void VertexBufferLayout::PushVertexAttribute<float>(unsigned int index, unsigned int count)
{
	if (m_VertexAttributes.size() > index)
	{
		VertexAttribute& va = m_VertexAttributes.at(index);
		m_Stride -= va.getAttributeSizeInBytes();
		va = { index, count, GL_FLOAT, GL_FALSE };
	}

	else
	{
		m_VertexAttributes.push_back({ index, count, GL_FLOAT, GL_FALSE });
	}

	m_Stride += (count * sizeof(GLfloat));
}

template <>
void VertexBufferLayout::PushVertexAttribute<unsigned int>(unsigned int index, unsigned int count)
{
	if (m_VertexAttributes.size() > index)
	{
		VertexAttribute& va = m_VertexAttributes.at(index);
		m_Stride -= va.getAttributeSizeInBytes();
		va = { index, count, GL_UNSIGNED_INT, GL_FALSE };
	}

	else
	{
		m_VertexAttributes.push_back({ index, count, GL_UNSIGNED_INT, GL_FALSE });
	}

	m_Stride += (count * sizeof(GLuint));
}

template <>
void VertexBufferLayout::PushVertexAttribute<unsigned char>(unsigned int index, unsigned int count)
{
	if (m_VertexAttributes.size() > index)
	{
		VertexAttribute& va = m_VertexAttributes.at(index);
		m_Stride -= va.getAttributeSizeInBytes();
		va = { index, count, GL_UNSIGNED_BYTE, GL_TRUE };
	}

	else
	{
		m_VertexAttributes.push_back({ index, count, GL_UNSIGNED_BYTE, GL_TRUE });
	}

	m_Stride += (count * sizeof(GLubyte));
}
