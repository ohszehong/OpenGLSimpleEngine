#pragma once

#include "Test.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include <vector>
#include <iostream>
#include <time.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestTexture.h"
#include "TestProjection.h"

namespace TestCase 
{
	struct Quad
	{
	public:
		float vertices[44];
		int selectedTexture;

		Quad() : selectedTexture(0)
		{
			srand(time(0));

			int index = 0;
			int nthVertex = 0;

			//method for random numbers involving upper bound and lower bound for future reference
			/*float lower_bound =  0.0f;
			float upper_bound =  2.0f;
			vertices[index] = (fmod((static_cast<float>(rand())), (upper_bound - lower_bound + 1))) - 1.0f;*/

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					//positions
					vertices[index] = ((static_cast<float>(rand()) / RAND_MAX) + (static_cast<float>(rand()) / RAND_MAX)) - 1.0f;
					index++;
				}

				for (int k = 0; k < 4; k++)
				{
					//color
					if (k == 3)
						vertices[index] = 1.0f;
					else 
						vertices[index] = (static_cast<float>(rand()) / RAND_MAX);

					index++;
				}

				for (int l = 0; l < 2; l++)
				{
					//texture coordinates					
					//vertices[index] = (static_cast<float>(rand()) / RAND_MAX);
					if (nthVertex == 0)
						vertices[index] = 0.0f;

					else if (nthVertex == 1)
						vertices[index] = (l == 0) ? 1.0f : 0.0f;

					else if (nthVertex == 2)
						vertices[index] = 1.0f;

					else if (nthVertex == 3)
						vertices[index] = (l == 0) ? 0.0f : 1.0f;

					index++;
				}

				//texture sampler index 
				vertices[index] = 0.0f;
				index++;

				//model matrix position
				vertices[index] = 0.0f;
				index++;
				vertices[index] = 0.0f;
				index++;

				nthVertex++;
			}

		};

		void PrintVertices()
		{
			for (int i = 0; i < 44; i++)
			{
				std::cout << "value: " << vertices[i] << std::endl;
			}
		}

	};

	class TestDrawQuad : public Test
	{
	private:
		std::vector<Quad> quads;
		Shader* shaderProgram;
		Renderer* renderer;
		VertexBuffer* vb;
		IndexBuffer* ib;
		VertexBufferLayout* layout;
		TestCase::TestTexture* textureTest;
		TestCase::TestProjection* projectionTest;
		unsigned int MAX_QUADS;

	public:
		TestDrawQuad(Shader* shaderProgram, Renderer* renderer, VertexBuffer* vb, IndexBuffer* ib, VertexBufferLayout* layout, TestCase::TestTexture* textureTest, TestCase::TestProjection* projectionTest, unsigned int MAX_QUADS);
		~TestDrawQuad();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		void generateQuad();

		inline std::vector<Quad>& getQuads()
		{
			return quads;
		}
	
	};

}