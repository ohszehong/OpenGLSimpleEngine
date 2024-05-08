#pragma once
#include <iostream>
#include <initializer_list>

class IndexBuffer
{
private:
	unsigned int m_bufferId;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(std::initializer_list<unsigned int> indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const
	{
		return m_Count;
	}

	inline unsigned int GetBufferId() const
	{
		return m_bufferId;
	}

	inline void SetCount(unsigned int newCount)
	{
		m_Count = newCount;
	}
};