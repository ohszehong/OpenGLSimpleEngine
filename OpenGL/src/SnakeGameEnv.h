#pragma once

#include <vector>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include "SnakeFood.h"
#include "Snake.h"
#include "ScoreBoard.h"
#include "TextRenderer.h"

#include "glm/gtc/matrix_transform.hpp"

namespace SnakeGame
{
	class SnakeGameEnv : public Entity
	{
		private:
			ScoreBoard scoreBoard;

			std::vector<float> vb_Data;
			std::vector<unsigned int> ib_Data;

			VertexArray VAO;
			VertexBufferLayout layout;
			Shader shaderProgram;
			Renderer renderer;

			SnakeFood snakeFood; 
			Snake snake;

			VertexBuffer vb;
			IndexBuffer ib;

			GLFWwindow* window;
			TextRenderer* textRenderer;
			int screenWidth, screenHeight;

		public:
			static bool GameOver;

			SnakeGameEnv(GLFWwindow* window, TextRenderer* textRenderer);
			~SnakeGameEnv();

			void onUpdate(double deltaTime, bool& gameState) override;
			void onRender();

			inline void Clear()
			{
				GLCall(glClear(GL_COLOR_BUFFER_BIT));
			}

			inline Snake* getSnake() 
			{
				return &snake;
			}

			inline TextRenderer& getTextRenderer()
			{
				return *textRenderer;
			}
	};
}
