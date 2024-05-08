#pragma once

#include "Test.h"
#include "Shader.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace TestCase
{
	class TestProjection : public Test
	{
	private:
		float MAX_LEFT;
		float MAX_RIGHT;
		float MAX_TOP;
		float MAX_BTM;

		float orthoValues[4];
		glm::vec3 viewVectors;
		Shader* shaderProgram;

	public:
		TestProjection(Shader* shaderProgram);
		~TestProjection();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		inline const glm::vec3& getViewVectors() const
		{
			return viewVectors;
		}

		inline const float* getOrthoValues() const
		{
			return orthoValues;
		}

		inline float getMaxLeft() const
		{
			return MAX_LEFT;
		}

		inline float getMaxRight() const
		{
			return MAX_RIGHT;
		}

		inline float getMaxBtm() const
		{
			return MAX_BTM;
		}

		inline float getMaxTop() const
		{
			return MAX_TOP;
		}
	};
}