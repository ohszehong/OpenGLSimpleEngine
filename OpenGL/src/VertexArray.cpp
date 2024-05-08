#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	std::cout << "VertexArray created!" << std::endl;
	GLCall(glGenVertexArrays(1, &m_VertexArrayId));
	std::cout << "VertexArray Id: " << m_VertexArrayId << std::endl;
	Bind();
}

VertexArray::~VertexArray()
{
	std::cout << "VertexArray deleted!" << std::endl;
	GLCall(glDeleteVertexArrays(1, &m_VertexArrayId));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_VertexArrayId));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBufferWithLayout(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	//ASSERT(layout.getVertexAttributes().size() > 0);

	vb.Bind();
	unsigned int offset = 0;

	for (const VertexAttribute& VA : layout.getVertexAttributes())
	{
		GLCall(glEnableVertexAttribArray(VA.index));
		GLCall(glVertexAttribPointer(VA.index, VA.count, VA.typeId, VA.normalized, layout.getStride(), (void*)offset));

		offset += VA.getAttributeSizeInBytes();
	}
	
	//vb.Unbind();
}

