#pragma once

class VertexBuffer
{
private:
	unsigned int m_bufferId;
	unsigned int size;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getBufferSize() const
	{
		return size;
	}

	inline void setBufferSize(unsigned int newSize)
	{
		size = newSize;
	}
};