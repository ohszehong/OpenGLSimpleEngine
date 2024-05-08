#include "TestDrawQuad.h"
#include <iostream>
#include <functional>

TestCase::TestDrawQuad::TestDrawQuad(Shader* shaderProgram, Renderer* renderer, VertexBuffer* vb, IndexBuffer* ib, VertexBufferLayout* layout, TestCase::TestTexture* textureTest, TestCase::TestProjection* projectionTest, unsigned int MAX_QUADS) : shaderProgram(shaderProgram), renderer(renderer), vb(vb), ib(ib), layout(layout), textureTest(textureTest), projectionTest(projectionTest), MAX_QUADS(MAX_QUADS)
{
	std::cout << "Initializing TestDrawQuad instance in TestWrapper..." << std::endl;
}

TestCase::TestDrawQuad::~TestDrawQuad()
{
	std::cout << "TestDrawQuad deleted!" << std::endl;
}

void TestCase::TestDrawQuad::onUpdate(float deltaTime)
{
}

void TestCase::TestDrawQuad::onRender()
{
	renderer->Draw(*ib);
}

void TestCase::TestDrawQuad::onImGuiRender()
{
	std::vector<const char*> selectableTextures;
	selectableTextures.reserve(textureTest->GetTextures().size());
	std::vector<std::string> tempTextureStrings;
	tempTextureStrings.reserve(textureTest->GetTextures().size());

	int textureCount = 0;
	for (Texture& texture : textureTest->GetTextures())
	{
		tempTextureStrings.emplace_back(std::to_string(textureCount));
		selectableTextures.emplace_back(tempTextureStrings[textureCount].c_str());
		textureCount++;
	}

	const char* defaultNA[] = {"N/A"};

	ImGui::Text("Quads Configuration");
	ImGui::Spacing();
	int quadCounter = 0;
	int vertexCounter = 0;

	for (Quad& quad : quads)
	{
		std::string QuadLabel = std::string("Quad ") + std::to_string(quadCounter);

		ImGui::Text(QuadLabel.c_str());

		ImGui::Spacing();

		if (ImGui::SliderFloat2((QuadLabel + std::string(" Vertex 1")).c_str(), quad.vertices, -1.0f, 1.0f))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}

		if (ImGui::ColorEdit4((QuadLabel + std::string(" Vertex 1 Color")).c_str(), quad.vertices + 2))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, ((vertexCounter * layout->getStride()) + (2 * sizeof(float))), 4 * sizeof(float), quad.vertices + 2));
		}
		vertexCounter++;

		if (ImGui::SliderFloat2((QuadLabel + std::string(" Vertex 2")).c_str(), quad.vertices + 11, -1.0f, 1.0f))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}

		if (ImGui::ColorEdit4((QuadLabel + std::string(" Vertex 2 Color")).c_str(), quad.vertices + 13))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, ((vertexCounter * layout->getStride()) + (2 * sizeof(float))), 4 * sizeof(float), quad.vertices + 13));
		}
		vertexCounter++;

		if (ImGui::SliderFloat2((QuadLabel + std::string(" Vertex 3")).c_str(), quad.vertices + 22, -1.0f, 1.0f))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}

		if (ImGui::ColorEdit4((QuadLabel + std::string(" Vertex 3 Color")).c_str(), quad.vertices + 24))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, ((vertexCounter * layout->getStride()) + (2 * sizeof(float))), 4 * sizeof(float), quad.vertices + 24));
		}
		vertexCounter++;

		if (ImGui::SliderFloat2((QuadLabel + std::string(" Vertex 4")).c_str(), quad.vertices + 33, -1.0f, 1.0f))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}

		if (ImGui::ColorEdit4((QuadLabel + std::string(" Vertex 4 Color")).c_str(), quad.vertices + 35))
		{
			GLCall(glBufferSubData(GL_ARRAY_BUFFER, ((vertexCounter * layout->getStride()) + (2 * sizeof(float))), 4 * sizeof(float), quad.vertices + 35));
		}
		vertexCounter++;

		ImGui::Spacing();

		if (ImGui::SliderFloat2((QuadLabel + std::string(" Model Matrix")).c_str(), quad.vertices + 9, projectionTest->getMaxLeft(), projectionTest->getMaxRight()))
		{
			//skip 10th and 11th element in vertices array because SliderFloat2 will directly change their values
			quad.vertices[20] = quad.vertices[9];
			quad.vertices[21] = quad.vertices[10];

			quad.vertices[31] = quad.vertices[9];
			quad.vertices[32] = quad.vertices[10];
							  
			quad.vertices[42] = quad.vertices[9];
			quad.vertices[43] = quad.vertices[10];

			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}
	
		ImGui::Spacing();

		if(ImGui::Combo((QuadLabel + std::string(" Texture")).c_str(), &quad.selectedTexture, (textureCount == 0 ? defaultNA : selectableTextures.data()), (textureCount == 0 ? 1 : selectableTextures.size())))
		{
			quad.vertices[8] = (float)quad.selectedTexture;
			quad.vertices[19] = (float)quad.selectedTexture;
			quad.vertices[30] = (float)quad.selectedTexture;
			quad.vertices[41] = (float)quad.selectedTexture;

			GLCall(glBufferSubData(GL_ARRAY_BUFFER, (quadCounter * 4 * layout->getStride()), 4 * layout->getStride(), quad.vertices));
		}

		quadCounter++;
	}
	ImGui::Spacing();
}

void TestCase::TestDrawQuad::generateQuad()
{
	if (quads.size() == MAX_QUADS)
	{	
		std::cout << "MAX_QUADS achieved! unable to add more quad." << std::endl;
		return;
	}

	quads.emplace_back();

	quads.back().PrintVertices();
	std::cout << "Total quads: " << quads.size() << std::endl;

	std::cout << "stride in bytes: " << layout->getStride() << std::endl;
	 
	//update vertex buffer
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)(4 * ((quads.size() - 1) * layout->getStride())), 4 * layout->getStride(), quads.back().vertices));
}


