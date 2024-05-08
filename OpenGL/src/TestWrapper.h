#pragma once

#include <vector>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "TestClearColor.h"
#include "TestDrawQuad.h"
#include "TestTexture.h"
#include "TestProjection.h"

class TestWrapper
{
private:
	enum class SelectedTest
	{
		NONE,
		TEST_CLEAR_COLOR,
		TEST_DRAW_QUAD,
		TEST_TEXTURE,
		TEST_PROJECTION
	};

	std::vector<std::string> m_Buttons; 
	SelectedTest m_RunTest;
	ImGuiContext* context;
	VertexArray VAO;
	Shader shaderProgram;
	Renderer renderer;
	VertexBuffer vb;
	IndexBuffer ib;
	VertexBufferLayout layout;
	TestCase::TestClearColor m_ClearColorTest;
	TestCase::TestTexture m_TextureTest;
	TestCase::TestProjection m_ProjectionTest;
	TestCase::TestDrawQuad m_DrawQuadTest;
	std::string m_Title;
	bool runningTest[4] = { false, false, false ,false };
	static constexpr unsigned int defaultIndices[] =
	{
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,

		24,25,26,
		26,27,24,

		28,29,30,
		30,31,28
	};
	bool enableTexture = false;

public:

	TestWrapper(GLFWwindow* window, std::string shaderFilePath, std::string title = "TESTS MENU");
	~TestWrapper();

	void AddButton(const char* label);

	void Render();

	void Clear();
};