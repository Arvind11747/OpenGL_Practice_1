#pragma once

#include <memory>
#include "Test.h"
#include "glm/glm.hpp"
#include "Renderer.h"
#include "Texture.h"

namespace Tests 
{
	class TestShader : public Test
	{
	public:
		TestShader();
		~TestShader();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender(std::string windowName) override;
	};
}