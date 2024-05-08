#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : vb(nullptr, 6 * 4 * sizeof(float))
{
	layout.PushVertexAttribute<float>(0, 2);
	layout.PushVertexAttribute<float>(1, 2);

	VAO.AddBufferWithLayout(vb, layout);

	ScoreBoard::score = 0;
}

ScoreBoard::~ScoreBoard()
{
}


