//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

//System (C++)
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//Custom headers
#include "GLErrorHandle.h"

#include "Renderer.h"
#include "Texture.h"
#include "Blending.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

float width=980.0f, height=540.0f;



glm::mat4 SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection) 
{
    return projection * view * model;
}

int main() {
  GLFWwindow* window;

  if (!glfwInit()) {
    return -1;
  }

  /*Setting version and Profile*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "Test", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Render context
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) 
  {
    std::cout << "Error: Rendering context not created" << std::endl;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  {
    float vertices[] = {
    /*0*/ /*Pc:*/ -50.0f, -50.0f, /*Tc:*/ 1.0f, 1.0f,
    /*1*/ /*Pc:*/ -50.0f,  50.0f, /*Tc:*/ 1.0f, 0.0f,
    /*2*/ /*Pc:*/  50.0f,  50.0f, /*Tc:*/ 0.0f, 0.0f,
    /*3*/ /*Pc:*/  50.0f, -50.0f, /*Tc:*/ 0.0f, 1.0f 
    };   


    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(4 * 4 * sizeof(float), vertices);
    VertexBufferLayout layout;
    layout.Push<float>(2); // Pc
    layout.Push<float>(2); // Tc
    va.AddBuffer(vb, layout);
    IndexBuffer ib(6, indices);
    
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    Texture texture("res/tex/tex1.png", false);
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    //ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));


    /*Clear bindings.*/
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    glm::vec3 translationA(0, 0, 0);
    glm::vec3 translationB(0, 0, 0);
    glm::vec3 camTranslation(0, 0, 0);

    glm::vec3 rotationAxisX(1, 0, 0);
    glm::vec3 rotationAxisY(0, 1, 0);
    glm::vec3 rotationAxisZ(0, 0, 1);

    float angleX=0.0f;
    float angleY=0.0f;
    float angleZ=45.0f;

    float moveCam=0;
    float i = 0.05;
    while (!glfwWindowShouldClose(window)) 
    {
        renderer.Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.Bind();
        {
            glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 modelRotation = glm::rotate(angleZ, rotationAxisZ); // Rotate on Z axis
            glm::mat4 modelScale = glm::scale(glm::vec3(2, 2, 1));

            glm::mat4 model = modelTranslate * modelRotation * modelScale;
            glm::mat4 view = glm::translate(glm::mat4(1.0f), camTranslation);
            glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

            glm::mat4 mvp = SetMVP(model, view, proj);

            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va,ib,shader);
        } 
        {
            glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 modelRotation = glm::rotate(angleZ, rotationAxisZ); // Rotate on Z axis
            glm::mat4 modelScale = glm::scale(glm::vec3(2, 2, 1));

            glm::mat4 model = modelTranslate * modelRotation * modelScale;
            glm::mat4 view = glm::translate(glm::mat4(1.0f), camTranslation);
            glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);

            glm::mat4 mvp = SetMVP(model, view, proj);

            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va,ib,shader);
        }

        {
            ImGui::Begin("Debuging Performance");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        {
            ImGui::Begin("Object Control");

            
            ImGui::Text("Object translate 1");
            ImGui::SliderFloat3("translate A", &translationA.x, 0.0f, 1000);            
            ImGui::NewLine();
            ImGui::Text("Object translate 2");
            ImGui::SliderFloat3("translate B", &translationB.x, 0.0f, 1000);
            ImGui::NewLine();
            ImGui::Text("Angle");
            ImGui::SliderAngle("Angle", &angleZ);

            
            ImGui::End();
        } 
        {
            ImGui::Begin("Camera Control");

            ImGui::Text("Camera translate");
            ImGui::SliderFloat3("cam", &camTranslation.x, 0.0f, 1000);
            ImGui::End();
        }

        //ImGui Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      /*Swap front and back buffers */
      glfwSwapBuffers(window);

      /*Poll for and process events */
      glfwPollEvents();


    }

    //GLCall(glDeleteProgram(shader));
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}