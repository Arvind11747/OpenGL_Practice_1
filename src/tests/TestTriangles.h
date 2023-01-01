#pragma once

#include <memory>
#include "Test.h"
#include "glm/glm.hpp"
#include "Renderer.h"
#include "Texture.h"

namespace Tests 
{
	class TestTriangles : public Test
	{
	public:
		 TestTriangles();
		~TestTriangles();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender(std::string windowName) override;

		static glm::mat4 SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	private:

		float m_Width, m_Height, m_AngleX, m_AngleY, m_AngleZ;
		glm::mat4 m_Projection, m_View;

		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		glm::vec3 m_CamTranslation;
		glm::mat3 m_RotationAxis;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		//std::unique_ptr<Texture> m_Texture;

		
	};
}