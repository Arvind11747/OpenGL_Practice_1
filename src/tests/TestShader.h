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
		static glm::mat4 SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		TestShader();
		~TestShader();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender(std::string windowName) override;
	private:
		float m_ambientStrength;
		std::unique_ptr<Shader> m_s_lighting;
		std::unique_ptr<Shader> m_s_light;
		unsigned int m_cubeVBO, m_VAO, m_LightVAO;
		
		

		glm::mat4 m_Projection, m_View;
		glm::vec3 m_CamTranslation;
		glm::vec3 lightPos;
	};
}