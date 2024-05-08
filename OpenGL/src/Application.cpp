//Internal
#include "Renderer.h"
#include "Texture.h"
#include "TestWrapper.h"
#include "SnakeGameEnv.h"

//3rd Party
//GLFW
#include <GLFW/glfw3.h>

//GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

#define LOG(x) std::cout << x << std::endl

int SnakeGame::Snake::direction;
bool SnakeGame::SnakeGameEnv::GameOver;
int ScoreBoard::score;

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 1280, "OpenGL Tests", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(4);

    if (glewInit() != GLEW_OK)
        LOG("Glew Init Failed.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //Graphic Testing 
    //TestWrapper testWrapper(window, "res/shaders/TestDrawQuads.shade");
    //testWrapper.AddButton("Test Clear Color");
    //testWrapper.AddButton("Test Draw Quad");
    //testWrapper.AddButton("Test Texture");
    //testWrapper.AddButton("Test Projection");

    //For any test 
    /*float vertices[] = {
        0.8f, 0.2f,
       -0.8f, 0.2f,
       -0.8f, 0.5f,
        0.8f, 0.5f
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };*/

    //VertexArray VAO;
    //VertexBuffer vb(vertices, 8 * sizeof(float));
    //IndexBuffer ib(indices, 6 * sizeof(unsigned int));

    //VertexBufferLayout layout; 
    //layout.PushVertexAttribute<float>(0, 2);
    //VAO.AddBufferWithLayout(vb, layout);
    //Shader shaderProgram("res/shaders/SnakeGame.shade");
    //shaderProgram.SetUniform4F("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    //Renderer renderer;
    

    //Snake Game 
    static TextRenderer textRenderer;

    SnakeGame::SnakeGameEnv::GameOver = false;
    static std::unique_ptr<SnakeGame::SnakeGameEnv> snakeGameEnv = std::make_unique<SnakeGame::SnakeGameEnv>(window, &textRenderer);

    double snakeMoveSpeedInSecond = snakeGameEnv.get()->getSnake()->GetMoveSpeedInSecond();
    double lastFrameTime = glfwGetTime();

    static double lastFrameTimeForKeyCallback = glfwGetTime();

    //Set key callback
    GLCall(glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

        double lastUpdateTimeForKeyCallback = glfwGetTime();

        double deltaTime = lastUpdateTimeForKeyCallback - lastFrameTimeForKeyCallback; 

        lastFrameTimeForKeyCallback = lastUpdateTimeForKeyCallback;

        if (deltaTime < 0.10)
            return;

        if (SnakeGame::SnakeGameEnv::GameOver)
        {
            if (action == GLFW_PRESS)
            {
                SnakeGame::SnakeGameEnv::GameOver = false;
                snakeGameEnv.reset();
                snakeGameEnv = std::make_unique<SnakeGame::SnakeGameEnv>(window, &textRenderer);
            }
            return;
        }

        if (key == GLFW_KEY_UP && SnakeGame::Snake::direction != GLFW_KEY_DOWN)
        {
            SnakeGame::Snake::direction = GLFW_KEY_UP;
        }

        else if (key == GLFW_KEY_DOWN && SnakeGame::Snake::direction != GLFW_KEY_UP)
        {
            SnakeGame::Snake::direction = GLFW_KEY_DOWN;
        }

        else if (key == GLFW_KEY_LEFT && SnakeGame::Snake::direction != GLFW_KEY_RIGHT)
        {
            SnakeGame::Snake::direction = GLFW_KEY_LEFT;
        }

        else if (key == GLFW_KEY_RIGHT && SnakeGame::Snake::direction != GLFW_KEY_LEFT)
        {
            SnakeGame::Snake::direction = GLFW_KEY_RIGHT;
        }
        }));

    LOG(glGetString(GL_VERSION));
    {
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
           GLCall(glViewport(0, 0, width, height));
        });

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            //Graphic Testing 
            //testWrapper.Clear();
            //testWrapper.Render();

            //Any test 
            //renderer.Draw(ib);

            ///* Poll for and process events */
            glfwPollEvents();

            if (SnakeGame::SnakeGameEnv::GameOver)
                continue;

            double currentTime = glfwGetTime();
            double deltaTime = currentTime - lastFrameTime;

            if (deltaTime >= snakeMoveSpeedInSecond)
            {
                lastFrameTime = currentTime;
            }
            snakeGameEnv.get()->onUpdate(deltaTime, SnakeGame::SnakeGameEnv::GameOver);
            snakeGameEnv.get()->onRender();
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            snakeGameEnv.get()->Clear();
        }
    }

    glfwTerminate();
    return 0;
}

