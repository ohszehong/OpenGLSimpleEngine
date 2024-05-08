#include "Renderer.h"
#include "Snake.h"
#include <iostream>

SnakeGame::Snake::Snake(std::vector<float>& vb_Data, std::vector<unsigned int>& ib_Data) : moveSpeedInSecond(0.5), vb_Data(vb_Data), ib_Data(ib_Data)
{
	//then, initialize snake with one head and two bodies
	//vertex 1 position 
	vb_Data[8] = -0.05f;
	vb_Data[9] = -0.05f;

	//vertex 2 position
	vb_Data[10] = -0.025f;
	vb_Data[11] = -0.05f;

	//vertex 3 position
	vb_Data[12] = -0.025f;
	vb_Data[13] = -0.025f;

	//vertex 4 position 
	vb_Data[14] = -0.05f;
	vb_Data[15] = -0.025f;

	//body2 
	vb_Data[16] = vb_Data[14];
	vb_Data[17] = vb_Data[15];

	vb_Data[18] = vb_Data[12];
	vb_Data[19] = vb_Data[13];

	vb_Data[20] = vb_Data[18];
	vb_Data[21] = vb_Data[19] + 0.025f;

	vb_Data[22] = vb_Data[16];
	vb_Data[23] = vb_Data[17] + 0.025f;

	//body3 
	vb_Data[24] = vb_Data[22];
	vb_Data[25] = vb_Data[23];

	vb_Data[26] = vb_Data[20];
	vb_Data[27] = vb_Data[21];

	vb_Data[28] = vb_Data[26];
	vb_Data[29] = vb_Data[27] + 0.025f;

	vb_Data[30] = vb_Data[24];
	vb_Data[31] = vb_Data[25] + 0.025f;
}

SnakeGame::Snake::~Snake()
{
}

void SnakeGame::Snake::onUpdate(double deltaTime, bool& gameState)
{
	//extend size if almost meet the end 
	if (vb_Data.capacity() - vb_Data.size() <= 8)
	{
		vb_Data.reserve(vb_Data.size() + 80);
	}

	if (ib_Data.capacity() - ib_Data.size() <= 6)
	{
		ib_Data.reserve(ib_Data.size() + 60);
	}

	//1) check if head touch body
	//2) check if head touch food 

	//only need to compare vertex 1's x and y for the head, body and food. 

	for (int i = 16; i < vb_Data.size(); i+=8)
	{
		if (isEqual(vb_Data[8], vb_Data[i]) && isEqual(vb_Data[9], vb_Data[i + 1]))
		{
			gameState = true;
			return;
		}
	}

	//get x range and y range of snake food from vb_Data
	if (isEqual(vb_Data[8], vb_Data[0]) && isEqual(vb_Data[9], vb_Data[1]))
	{
		//change snakeFood position and increase snake body
		float firstX = (rand() % 80) * 0.025f;
		float firstY = (rand() % 80) * 0.025f;

		if (firstX < 1.0f)
		{
			firstX = firstX * -1.0f;
		}

		else if (firstX == 2.0f)
		{
			firstX = firstX - 1.025f;
		}

		else if (firstX >= 1.0f)
		{
			firstX = firstX - 1.0f;
		}

		if (firstY < 1.0f)
		{
			firstY = firstY * -1.0f;
		}

		else if (firstY == 2.0f)
		{
			firstY = firstY - 1.025f;
		}

		else if (firstY >= 1.0f)
		{
			firstY = firstY - 1.0f;
		}

		vb_Data[0] = firstX;
		vb_Data[1] = firstY;

		vb_Data[2] = vb_Data[0] + 0.025f;
		vb_Data[3] = vb_Data[1];

		vb_Data[4] = vb_Data[2];
		vb_Data[5] = vb_Data[3] + 0.025;

		vb_Data[6] = vb_Data[4] - 0.025f;
		vb_Data[7] = vb_Data[5];

		int lastItemIndex = vb_Data.size() - 1; 
		std::vector<float> tempVb =
		{
			vb_Data[lastItemIndex - 7], vb_Data[lastItemIndex - 6],
			vb_Data[lastItemIndex - 5], vb_Data[lastItemIndex - 4],
			vb_Data[lastItemIndex - 3], vb_Data[lastItemIndex - 2],
			vb_Data[lastItemIndex - 1], vb_Data[lastItemIndex]
		};
		
		vb_Data.insert(vb_Data.end(), tempVb.begin(), tempVb.end());

		if (moveSpeedInSecond >= 0.015)
		{
			moveSpeedInSecond -= 0.015;
		}

		unsigned int startVertexCount = ib_Data[ib_Data.size() - 2] + 1;

		std::vector<unsigned int> tempIb = {
			startVertexCount,
			startVertexCount + 1,
			startVertexCount + 2,
			startVertexCount + 2,
			startVertexCount + 3,
			startVertexCount
		};

		ib_Data.insert(ib_Data.end(), tempIb.begin(), tempIb.end());

		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, ib_Data.size() * sizeof(float), ib_Data.data()));

		ScoreBoard::score += 1;
	}
}

void SnakeGame::Snake::Move()
{
	//move based on direction -- change the vertices and sub data to the buffer in GPU
	for (int i = vb_Data.size() - 1; i > 15; i--)
	{
		vb_Data[i] = vb_Data[i - 8];
	}

	//change the vertices of the head only 
	for (int i = 8; i < 16; i++)
	{
		switch (direction)
		{
		case GLFW_KEY_UP:
			if (i % 2 != 0)
				vb_Data[i] = vb_Data[i] + 0.025f;
			break;

		case GLFW_KEY_DOWN:
			if (i % 2 != 0)
				vb_Data[i] = vb_Data[i] - 0.025f;
			break;

		case GLFW_KEY_LEFT:
			if (i % 2 == 0)
				vb_Data[i] = vb_Data[i] - 0.025f;
			break;

		case GLFW_KEY_RIGHT:
			if (i % 2 == 0)
				vb_Data[i] = vb_Data[i] + 0.025f;
			break;

		default:
			return;
			break;
		}
	}

	//check for when the quad pass over the edge of the screen, appear on the other side 
	if (vb_Data[13] > 1.025f)
	{
		vb_Data[9] = vb_Data[9] - 2.0f;
		vb_Data[11] = vb_Data[11] - 2.0f;
		vb_Data[13] = vb_Data[13] - 2.0f;
		vb_Data[15] = vb_Data[15] - 2.0f;

	}

	else if (vb_Data[9] < -1.025f)
	{
		vb_Data[9] = vb_Data[9] + 2.0f;
		vb_Data[11] = vb_Data[11] + 2.0f;
		vb_Data[13] = vb_Data[13] + 2.0f;
		vb_Data[15] = vb_Data[15] + 2.0f;
	}

	else if (vb_Data[8] < -1.025f)
	{
		vb_Data[8] = vb_Data[8] + 2.0f;
		vb_Data[10] = vb_Data[10] + 2.0f;
		vb_Data[12] = vb_Data[12] + 2.0f;
		vb_Data[14] = vb_Data[14] + 2.0f;
	}
	
	else if (vb_Data[10] > 1.025f)
	{
		vb_Data[8] = vb_Data[8] - 2.0f;
		vb_Data[10] = vb_Data[10] - 2.0f;
		vb_Data[12] = vb_Data[12] - 2.0f;
		vb_Data[14] = vb_Data[14] - 2.0f;
	}
}
