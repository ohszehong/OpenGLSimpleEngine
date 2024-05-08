#include <time.h>

#include "SnakeFood.h"

SnakeGame::SnakeFood::SnakeFood(std::vector<float>& vb_Data) : vb_Data(vb_Data)
{
	/*vb_Data[0] = ((static_cast<float>(rand()) / RAND_MAX) + (static_cast<float>(rand()) / RAND_MAX)) - 1.0f;
	vb_Data[1] = ((static_cast<float>(rand()) / RAND_MAX) + (static_cast<float>(rand()) / RAND_MAX)) - 1.0f;*/

	srand(time(0));

	int max = 80;
	int random = (rand() % 80);
	int random2 = (rand() % 80);

	float firstX = random * 0.025f;
	float firstY = random2 * 0.025f;

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

	//vertex 1 position 
	vb_Data[0] = firstX;
	vb_Data[1] = firstY;

	//vertex 2 position 
	vb_Data[2] = vb_Data[0] + 0.025f;
	vb_Data[3] = vb_Data[1];

	//vertex 3 position 
	vb_Data[4] = vb_Data[2];
	vb_Data[5] = vb_Data[3] + 0.025;

	//vertex 4 position 
	vb_Data[6] = vb_Data[4] - 0.025f;
	vb_Data[7] = vb_Data[5];
}

SnakeGame::SnakeFood::~SnakeFood()
{
}

void SnakeGame::SnakeFood::onUpdate(double deltaTime, bool& gameState)
{
}
