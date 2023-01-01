//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Image library
#include <stb_image.h>

//System (C++)
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//Custom headers
#include "GLErrorHandle.h"

//Abstacted Classes
#include "Renderer.h"
#include "Texture.h"
#include "Blending.h"

//GLM headers
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

//Dear ImGui headers
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


//Tests
#include "tests/TestClearColor.h"
#include "tests/TestTriangles.h"
#include "tests/TestShader.h"


float width = 980.0f, height = 540.0f;



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
    Tests::TestClearColor testClearColor;
    //Tests::TestTriangles testTriangles;
      //Tests::TestShader testShaders;
      //Tests::testClearColorBlur testClearColor;


    //Renderer renderer;
    


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
    /*va.Unbind();
    vb.Unbind();
    ib.Unbind();*/
    //shader.Unbind();

    
    while (!glfwWindowShouldClose(window)) 
    {
        /*renderer.Clear();*/
        testClearColor.OnUpdate(0.0f);
        testClearColor.OnRender();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        testClearColor.OnImGuiRender("TestColor");
        //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
  
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