#pragma once

#include "Test.h"
#include "glm/glm.hpp"

namespace Tests 
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender(std::string windowName) override;

	private:
		float m_ClearColor[4];
	};
}