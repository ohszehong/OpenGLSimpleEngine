#pragma once

#include "Test.h"

namespace TestCase
{
	class TestClearColor : public Test
	{
	private:
		float m_Color[4];

	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender();
		
		void Reset();
	};
}
