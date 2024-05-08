#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"

class ScoreBoard
{
private:
	VertexArray VAO;
	VertexBuffer vb;
	VertexBufferLayout layout;

public:
	static int score;

	ScoreBoard();
	~ScoreBoard();

	inline VertexArray& getVAO() 
	{
		return VAO;
	}

	inline VertexBuffer& getVb()
	{
		return vb;
	}
};
