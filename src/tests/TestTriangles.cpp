
#include "TestTriangles.h"

#include "GL/glew.h"
#include "imgui/imgui.h"
#include "GLErrorHandle.h" 

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Tests
{
	glm::mat4 TestTriangles::SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		return projection * view * model;
	}
	TestTriangles::TestTriangles() :
		m_Width(920), m_Height(540), m_AngleX(0), m_AngleY(0), m_AngleZ(0),
		m_TranslationA(0, 0, -1000), m_TranslationB(600, 0, 35),
		m_CamTranslation(0, 0, 0), m_RotationAxis(glm::mat3(1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), m_CamTranslation)),
		m_Projection(glm::perspective(glm::radians(45.0f), 920.0f / 540.0f, 0.1f, 5000.0f))
	{
		float vertices[]={
					//Position Coords		//Texture Coords
			/*0*/	-50.0f, -50.0f, 0.0f,	1.0f, 1.0f,
			/*1*/	-50.0f,  50.0f, 0.0f,	1.0f, 0.0f,
			/*2*/	 50.0f,  50.0f, 0.0f,	0.0f, 0.0f,
			/*3*/	 50.0f, -50.0f, 0.0f,	0.0f, 1.0f
		};
		float vertices2[] = {
			/*0*/	-50.0f, -50.0f,  50.0f,  0.0f, 0.0f,
			/*1*/	 50.0f, -50.0f,  50.0f,  1.0f, 0.0f,
			/*2*/	 50.0f,  50.0f,  50.0f,  1.0f, 1.0f,
			/*3*/	-50.0f,  50.0f,  50.0f,  1.0f, 0.0f,

			/*4*/	-50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
			/*5*/	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
			/*6*/	 50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
			/*7*/	-50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
			
		};

		unsigned int indices[] = 
		{
			0, 1, 2,
			2, 3, 0
		};
		
		unsigned int indices2[] = 
		{
			7,6,5,
			5,4,7,

			0,1,2,
			2,3,0,

			3,4,7,
			7,0,3,

			2,5,6,
			6,1,0,

			7,6,1,
			1,0,7,

			4,5,2,
			2,3,4
		};

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(5*8*sizeof(float), vertices2);
		VertexBufferLayout layout;
		layout.Push<float>(3); // Pc
		layout.Push<float>(2); // Tc

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(36, indices2);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

		//m_Texture = std::make_unique<Texture>("res/tex/tex1.png", false);
		m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
		//m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTriangles::~TestTriangles()
	{
	}

	void TestTriangles::OnUpdate(float deltaTime)
	{

	}

	void TestTriangles::OnRender()
	{
		Renderer renderer;
		renderer.Clear();

		//m_Texture->Bind();

		m_View = glm::translate(glm::mat4(1.0f), m_CamTranslation);
		{
		    glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f),m_TranslationA);
			glm::mat4 modelRotation = glm::mat4(1.0f); // Rotate on Z axis
			glm::mat4 RotationX = glm::rotate(m_AngleX, m_RotationAxis[0]);
			glm::mat4 RotationY = glm::rotate(m_AngleY, m_RotationAxis[1]);
			glm::mat4 RotationZ = glm::rotate(m_AngleZ, m_RotationAxis[2]);
			modelRotation = RotationX * RotationY * RotationZ;
		    glm::mat4 modelScale = glm::scale(glm::vec3(2, 2, 2));

		    glm::mat4 model = modelTranslate * modelRotation * modelScale;

		    glm::mat4 mvp = SetMVP(model, m_View, m_Projection);
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
		    renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);
		} 
		//{
		//    glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f),m_TranslationB);
		//	glm::quat modelQuaternion;

		//	modelQuaternion = glm::angleAxis(glm::radians(m_AngleZ), m_RotationAxis[0]);
		//	glm::mat4 modelRotation = glm::toMat4(modelQuaternion);
		//   // glm::rotate(m_AngleX, m_RotationAxis[0]); // Rotate on Z axis
		//			//modelRotation = glm::rotate(m_AngleZ, m_RotationAxis[2]); // Rotate on Z axis
		//    glm::mat4 modelScale = glm::scale(glm::vec3(2, 2, 1));

		//    glm::mat4 model = modelTranslate * modelRotation * modelScale;

		//    glm::mat4 mvp = SetMVP(model, m_View, m_Projection);
		//	m_Shader->Bind();
		//	m_Shader->SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		//}
	}

	void TestTriangles::OnImGuiRender(std::string windowName)
	{

		{
		    ImGui::Begin("Debuging Performance");
		    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		    ImGui::End();
		}

		{
		    ImGui::Begin("Object Control");

		    
		    ImGui::Text("Object translate 1");
		    ImGui::SliderFloat3("translate A", &m_TranslationA.x, -20000.0f, 20000.0f);
		    ImGui::NewLine();
		    ImGui::Text("Object translate 2");
		    ImGui::SliderFloat3("translate B", &m_TranslationB.x, 0.0f, 1000);
			
			ImGui::NewLine();
		    ImGui::SliderAngle("Angle X", &m_AngleX);
						
			ImGui::NewLine();
		    ImGui::SliderAngle("Angle Y", &m_AngleY);

		    ImGui::NewLine();
		    ImGui::SliderAngle("Angle Z", &m_AngleZ);		    
			

		    
		    ImGui::End();
		} 
		{
		    ImGui::Begin("Camera Control");

		    ImGui::Text("Camera translate");
		    ImGui::SliderFloat3("cam", &m_CamTranslation.x, 0.0f, 1000);
		    ImGui::End();
		}
	}
}

