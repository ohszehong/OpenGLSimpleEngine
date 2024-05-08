#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_bufferId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
    std::cout << "IndexBuffer ID: " << m_bufferId << std::endl;
}

IndexBuffer::IndexBuffer(std::initializer_list<unsigned int> indices, unsigned int count) : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_bufferId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices.begin(), GL_DYNAMIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    std::cout << "Index Buffer Deleted!" << std::endl;
    GLCall(glDeleteBuffers(1, &m_bufferId));
}

void IndexBuffer::Bind() const
{
    //std::cout << "Index Buffer Bound!" << std::endl;
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
}

void IndexBuffer::Unbind() const
{
    //std::cout << "Index Buffer Unbind!" << std::endl;
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
