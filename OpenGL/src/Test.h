#pragma once

namespace TestCase
{

	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};

		virtual void onUpdate(float deltaTime) {};
		virtual void onRender() {};
		virtual void onImGuiRender() {};
	};

}