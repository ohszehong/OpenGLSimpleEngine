#include "TestProjection.h"

TestCase::TestProjection::TestProjection(Shader* shaderProgram) : MAX_LEFT(-2.0f), MAX_RIGHT(2.0f), MAX_BTM(-2.0f), MAX_TOP(2.0f), orthoValues{-1.0f, 1.0f, -1.0f, 1.0f}, viewVectors(glm::vec3(0.0f, 0.0f, 0.0f)), shaderProgram(shaderProgram)
{
	//set initial values for the uniforms in shader 
	glm::mat4 projection = glm::ortho(orthoValues[0], orthoValues[1], orthoValues[2], orthoValues[3], -1.5f, 1.5f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), getViewVectors());
	shaderProgram->SetUniformMat4("u_Projection", projection);
	shaderProgram->SetUniformMat4("u_View", view);
}

TestCase::TestProjection::~TestProjection()
{
}

void TestCase::TestProjection::onUpdate(float deltaTime)
{

}

void TestCase::TestProjection::onRender()
{
}

void TestCase::TestProjection::onImGuiRender()
{
	

	ImGui::Text("View Matrix");
	ImGui::Spacing();
	if (ImGui::SliderFloat3("Imaginary Camera", &viewVectors.x, MAX_LEFT, MAX_RIGHT))
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), getViewVectors());
		shaderProgram->SetUniformMat4("u_View", view);
	}
	
	ImGui::Spacing();

	ImGui::Text("Orthographic Projection");
	ImGui::Spacing();
	if (ImGui::SliderFloat("LEFT", orthoValues, MAX_LEFT, MAX_RIGHT))
	{
		glm::mat4 projection = glm::ortho(orthoValues[0], orthoValues[1], orthoValues[2], orthoValues[3], -1.5f, 1.5f);
		shaderProgram->SetUniformMat4("u_Projection", projection);
	}
	if(ImGui::SliderFloat("RIGHT", orthoValues + 1, MAX_LEFT, MAX_RIGHT))
	{
		glm::mat4 projection = glm::ortho(orthoValues[0], orthoValues[1], orthoValues[2], orthoValues[3], -1.5f, 1.5f);
		shaderProgram->SetUniformMat4("u_Projection", projection);
	}
	if(ImGui::SliderFloat("BOTTOM", orthoValues + 2, MAX_BTM, MAX_TOP))
	{
		glm::mat4 projection = glm::ortho(orthoValues[0], orthoValues[1], orthoValues[2], orthoValues[3], -1.5f, 1.5f);
		shaderProgram->SetUniformMat4("u_Projection", projection);
	}
	if(ImGui::SliderFloat("TOP", orthoValues + 3, MAX_BTM, MAX_TOP))
	{
		glm::mat4 projection = glm::ortho(orthoValues[0], orthoValues[1], orthoValues[2], orthoValues[3], -1.5f, 1.5f);
		shaderProgram->SetUniformMat4("u_Projection", projection);
	}
}
