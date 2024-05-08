#pragma once

#include <vector>
#include "ScoreBoard.h"
#include "GLFW\glfw3.h"

#include "GameEntity.h"

namespace SnakeGame
{
	class Snake : public Entity
	{
		private:
			double moveSpeedInSecond;
			std::vector<float>& vb_Data;
			std::vector<unsigned int>& ib_Data;

		public:
			static int direction;

			Snake(std::vector<float>& vb_Data, std::vector<unsigned int>& ib_Data);
			~Snake();
			void onUpdate(double deltaTime, bool& gameState) override;
			void Move();

			inline double GetMoveSpeedInSecond() const
			{
				return moveSpeedInSecond;
			}

			inline static void setDirection(int direction)
			{
				SnakeGame::Snake::direction = direction;
			}
	};
}