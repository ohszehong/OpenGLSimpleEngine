#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) : size(size)
{
    GLCall(glGenBuffers(1, &m_bufferId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));

    std::cout << "VertexBuffer ID: " << m_bufferId << std::endl;
}

VertexBuffer::~VertexBuffer()
{
    std::cout << "Vertex Buffer Deleted!" << std::endl;
    GLCall(glDeleteBuffers(1, &m_bufferId));
}

void VertexBuffer::Bind() const
{
    //std::cout << "Vertex Buffer Bound!" << std::endl;
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
}

void VertexBuffer::Unbind() const
{
    //std::cout << "Vertex Buffer Unbind!" << std::endl;
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
