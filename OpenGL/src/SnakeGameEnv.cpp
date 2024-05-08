#include "SnakeGameEnv.h"

SnakeGame::SnakeGameEnv::SnakeGameEnv(GLFWwindow* window, TextRenderer* textRenderer) : scoreBoard(), vb_Data(32), ib_Data({
	//snake food
	0,1,2,
	2,3,0,

	//snake initial head
	4,5,6,
	6,7,4,

	//snake intial body
	8,9,10,
	10,11,8,

	12,13,14,
	14,15,12
	}), snake(vb_Data, ib_Data), snakeFood(vb_Data), shaderProgram("res/shaders/SnakeGame.shade"), vb(nullptr, vb_Data.size() * sizeof(float)), ib(nullptr, ib_Data.size()), window(window), textRenderer(textRenderer)
{	
	//setting up vertex layout 
	layout.PushVertexAttribute<float>(0, 2);
	VAO.AddBufferWithLayout(vb, layout);

	//white color for snake and food 
	//shaderProgram.SetUniform4F("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	
	//set projection for text rendering 
	glfwGetWindowSize(window, &screenWidth, &screenHeight);
	shaderProgram.SetUniformMat4("u_Projection", glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight)));

	//initialize buffer in GPU 
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vb_Data.size() * sizeof(float), vb_Data.data()));
	
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, ib.GetCount() * sizeof(unsigned int), ib_Data.data()));

	//initial direction
	SnakeGame::Snake::direction = GLFW_KEY_DOWN;
}

SnakeGame::SnakeGameEnv::~SnakeGameEnv()
{
}

void SnakeGame::SnakeGameEnv::onUpdate(double deltaTime, bool& gameState)
{
	ib.Bind();
	snake.onUpdate(deltaTime, gameState);

	//if (deltaTime < snake.GetMoveSpeedInSecond())
	//{
	//	return;
	//}

	snake.Move();
}

void SnakeGame::SnakeGameEnv::onRender()
{
	if (SnakeGame::SnakeGameEnv::GameOver)
	{
		//Draw Game Over
		scoreBoard.getVAO().Bind();
		shaderProgram.SetUniform1i("u_WithTexCoords", 1);
		textRenderer->RenderText(shaderProgram, "GAME OVER", scoreBoard.getVb(), static_cast<float>(screenWidth * 0.40f), static_cast<float>(screenHeight * 0.51f), 1.5f, glm::vec4(0.5, 0.8f, 0.2f, 1.0f));
		textRenderer->RenderText(shaderProgram, "press any key to continue", scoreBoard.getVb(), static_cast<float>(screenWidth * 0.345f), static_cast<float>(screenHeight * 0.45f), 1.0f, glm::vec4(0.5, 0.8f, 0.2f, 1.0f));
	}

	//Draw Snake 
	VAO.Bind();
	vb.Bind();
	shaderProgram.SetUniform1i("u_WithTexCoords", 0);
	shaderProgram.SetUniform4F("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	if (vb.getBufferSize() - 32 <= vb_Data.size() * sizeof(float))
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, ((vb.getBufferSize()) + (80 * sizeof(float))), vb_Data.data(), GL_DYNAMIC_DRAW));
		vb.setBufferSize(vb.getBufferSize() + (80 * sizeof(float)));
	}

	if (ib.GetCount() - 6 <= ib_Data.size())
	{
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ib.GetCount() + 60) * sizeof(unsigned int), ib_Data.data(), GL_DYNAMIC_DRAW));
		ib.SetCount(ib.GetCount() + 60);
	}

	//give snake head different color 
	renderer.DrawWithCount(ib, ib_Data.size());

	//update buffers in GPU 
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vb_Data.size() * sizeof(float), vb_Data.data()));

	//Draw Score
	scoreBoard.getVAO().Bind();
	shaderProgram.SetUniform1i("u_WithTexCoords", 1);
	textRenderer->RenderText(shaderProgram, std::to_string(ScoreBoard::score), scoreBoard.getVb(), static_cast<float>(screenWidth * 0.51f), static_cast<float>(screenHeight * 0.9375f), 1.25f, glm::vec4(0.5, 0.8f, 0.2f, 1.0f));
}
