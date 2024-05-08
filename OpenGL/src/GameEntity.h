#pragma once


namespace SnakeGame
{
	class Entity
	{
	public:
		Entity() {}
		virtual ~Entity() {}

		virtual void onUpdate(double deltaTime, bool& gameState) {};
	};
}