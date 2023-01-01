#include "TestClearColor.h"

#include "GL/glew.h"
#include "imgui/imgui.h"

#include "GLErrorHandle.h" 
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

namespace Tests
{
	TestClearColor::TestClearColor() :
		m_CamTranslation(0, 0, 0), cameraFront(0.0f, 0.0f, -1.0f), cameraUp(0.0f, 1.0f, 0.0f),
		view(glm::lookAt(m_CamTranslation, m_CamTranslation + cameraFront, cameraUp)),
		projection(glm::perspective(glm::radians(45.0f), 920.0f / 540.0f, 0.1f, 5000.0f)),
		m_Translation(0, 0, -50),
		m_Scale(1, 1, 1)
	{
		shader = std::make_unique<Shader>("res/shaders/car1.shader");
		shader->Bind();

		object = std::make_unique<Model>("res/models/car.fbx");
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}


	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(0.1, 0.1, 0.1, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		//GLCall(glBindTexture(GL_TEXTURE_2D, Texture));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		shader->Bind();
		scale = glm::scale(model, m_Scale);
		translation = glm::translate(model, m_Translation);
		model = translation *  scale;
		glm::mat4 mvp = projection * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		object->Draw(*shader);

	}

	void TestClearColor::OnImGuiRender(std::string windowName)
	{

		{
			ImGui::Begin("Debuging Performance");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		{
			ImGui::Begin("Camera Control");

			ImGui::Text("Camera translate");
			ImGui::SliderFloat3("cam", &m_CamTranslation.x, -5.0f, 5.0f);

			ImGui::End();
		}
		{
			ImGui::Begin("Translation Control");

			ImGui::Text("Model translate");
			ImGui::SliderFloat3("model", &m_Translation.x, -200.0f, 200.0f);
			
			ImGui::Text("Model scale");
			ImGui::SliderFloat3("modelScale", &m_Scale.x, -500.0f, 500.0f);

			ImGui::End();
		}
		/*{
			ImGui::Begin("LightProperties");

			ImGui::Text("Ambient Strength");
			ImGui::SliderFloat("Ambient Strength", &m_ambientStrength, 0.0f, 1.0f);
			ImGui::Text("Light movement");
			ImGui::SliderFloat3("Light translation", &lightPos.x, -5.0f, 5.0f);
			ImGui::End();
		}*/
	}
}

