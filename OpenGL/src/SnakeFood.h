#pragma once

#include <vector>

#include "Snake.h"

namespace SnakeGame
{
	class SnakeFood : public Entity
	{
		private:
			std::vector<float>& vb_Data;

		public:
			SnakeFood(std::vector<float>& vb_Data);
			~SnakeFood();

			void onUpdate(double deltaTime, bool& gameState) override;
	};
}