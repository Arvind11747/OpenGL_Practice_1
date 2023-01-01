#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Model.h"
#include <memory>

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
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Model> object;
		//Model object("res/models/car.fbx");
		//Shader ("res/shaders/basic.shader");

		glm::mat4 model;

		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		glm::vec3 m_CamTranslation;
		glm::vec3 m_Translation;
		glm::vec3 m_Scale;

		glm::mat4 view;

		glm::mat4 projection;

		glm::mat4 translation;
		glm::mat4 rotation;
		glm::mat4 scale;
	};
}