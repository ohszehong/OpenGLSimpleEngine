#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"


TestCase::TestClearColor::TestClearColor() : m_Color{ 0.5f, 0.5f, 0.5f, 1.0f }
{
}

TestCase::TestClearColor::~TestClearColor()
{
	std::cout << "TestClearColor deleted!" << std::endl;
}

void TestCase::TestClearColor::onUpdate(float deltaTime)
{
}

void TestCase::TestClearColor::onRender()
{
	GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestCase::TestClearColor::onImGuiRender()
{
	ImGui::Text("Clear Color Configuration");
	ImGui::Spacing();
	ImGui::ColorEdit4("Clear Color", m_Color);
	ImGui::Spacing();
}

void TestCase::TestClearColor::Reset()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}



