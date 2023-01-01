
#include "TestMotionBlur.h"

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
    glm::mat4 TestMotionBlur::SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
    {
        return projection * view * model;
    }
    TestMotionBlur::TestMotionBlur() :
        m_CamTranslation(0, 0, 3),
        m_Projection(glm::perspective(glm::radians(45.0f), 920.0f / 540.0f, 0.1f, 5000.0f)),
        lightPos(0.2f, -1.0f, 0.0f),
        m_ambientStrength(0.1f)
	{
        //glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        GLCall(glEnable(GL_DEPTH_TEST));
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        };

        float vertices2[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        m_s_lighting = std::make_unique<Shader>("res/shaders/lighting.shader");
        m_s_light = std::make_unique<Shader>("res/shaders/light.shader");

        GLCall(glGenVertexArrays(1,&m_VAO));
        GLCall(glGenBuffers(1, &m_cubeVBO));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW));
        
        GLCall(glBindVertexArray(m_VAO));

        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
        GLCall(glEnableVertexAttribArray(0));

        GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float))));
        GLCall(glEnableVertexAttribArray(1));


        GLCall(glGenVertexArrays(1, &m_LightVAO));
        GLCall(glBindVertexArray(m_LightVAO));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO));

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);



	}

	TestMotionBlur::~TestMotionBlur()
	{

	}

	void TestMotionBlur::OnUpdate(float deltaTime)
	{

	}

	void TestMotionBlur::OnRender()
	{
        //Renderer renderer;
        //renderer.Clear();
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        m_View = glm::lookAt(m_CamTranslation, m_CamTranslation + cameraFront, cameraUp);

        m_s_lighting->Bind();
        m_s_lighting->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        m_s_lighting->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        m_s_lighting->SetUniform1f("ambientStrength",m_ambientStrength);
        m_s_lighting->SetUniformVec3("lightPos", lightPos);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0, -1.0f, -2.0f));
        glm::mat4 mvp = SetMVP(model, m_View, m_Projection);
        m_s_lighting->SetUniformMat4f("u_MVP", mvp);
        m_s_lighting->SetUniformMat4f("u_model", model);

        GLCall(glBindVertexArray(m_VAO));
        
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        m_s_light->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        mvp = SetMVP(model, m_View, m_Projection);
        m_s_light->SetUniformMat4f("u_MVP", mvp);

        GLCall(glBindVertexArray(m_LightVAO));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	}

	void TestMotionBlur::OnImGuiRender(std::string windowName)
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
            ImGui::Begin("LightProperties");

            ImGui::Text("Ambient Strength");
            ImGui::SliderFloat("Ambient Strength", &m_ambientStrength, 0.0f, 1.0f);    
            ImGui::Text("Light movement");
            ImGui::SliderFloat3("Light translation", &lightPos.x, -5.0f, 5.0f);
            ImGui::End();
        }
       
	}
}

