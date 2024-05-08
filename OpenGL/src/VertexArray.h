#pragma once

#include "DebugUtilities.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
private:
	unsigned int m_VertexArrayId;
	
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBufferWithLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);

	inline unsigned int GetVertexArrayId() const
	{
		return m_VertexArrayId;
	}
};

