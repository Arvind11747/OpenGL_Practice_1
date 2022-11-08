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

float width=980.0f, height=540.0f;

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

  if (glewInit() != GLEW_OK) {
    std::cout << "Error: Rendering context not created" << std::endl;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  {
    float vertices[] = {
    /*0*/ /*Pc:*/ 100.0f, 100.0f, /*Tc:*/ 1.0f, 1.0f,
    /*1*/ /*Pc:*/ 100.0f, 200.0f, /*Tc:*/ 1.0f, 0.0f,
    /*2*/ /*Pc:*/ 200.0f, 200.0f, /*Tc:*/ 0.0f, 0.0f,
    /*3*/ /*Pc:*/ 200.0f, 100.0f, /*Tc:*/ 0.0f, 1.0f 
    };   


    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /*Vertex Array Object (Abstracted to class VertexArray)*/
    //unsigned int vao;
    //GLCall(glGenVertexArrays(1, &vao));
    //GLCall(glBindVertexArray(vao));

    /* Buffer Example code (Abstacted to class VertexBuffer)
    unsigned int buffer;
    //Generate Buffer
    GLCall(glGenBuffers(1, &buffer));
    //Bind that Buffer to a buffer binding object
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    //Creates a new data store for the buffer object currently bound to target
    (GL_ARRAY_BUFFER). GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
    vertices, GL_STATIC_DRAW));
    */
    

    /*//Example Code (Abstracted to class VertexArray)
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
    */

    /*Indices Object Buffer Example code (Abstacted to class IndexBuffer)
    unsigned int ibo;
    //Generate Buffer
    GLCall(glGenBuffers(1, &ibo));
    //Bind that Buffer to a buffer binding object
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    //Creates a new data store for the buffer object currently bound to target
    (GL_ELEMENT_ARRAY_BUFFER). GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    sizeof(indices), indices, GL_STATIC_DRAW));
    */
    
    VertexArray va;
    VertexBuffer vb(4 * 4 * sizeof(float), vertices);
    VertexBufferLayout layout;
    layout.Push<float>(2); // Pc
    layout.Push<float>(2); // Tc
    va.AddBuffer(vb, layout);
    IndexBuffer ib(6, indices);

    Renderer renderer;


    /* Shader (Abstracted into class Shader)
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    // std::cout << "Vertex Shader" << std::endl;
    // std::cout << source.VertexSource << std::endl;
    // std::cout << "Fragment Shader" << std::endl;
    // std::cout << source.FragmentSource << std::endl;
    //Creating Shader by parsing the shader from different file
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    */
    /*Installs the program object specified by program as part of current
     * rendering state. */
    //GLCall(glUseProgram(shader));
    /*Uniform to control Color*/
    // Get the location of the uniform from the shader.
    //GLCall(int color_Location = glGetUniformLocation(shader, "u_color"));
    // Check to see if the uniform is present in the shader or not.;
    //ASSERT(color_Location != -1);
    // Send the location and the value through here.
    //GLCall(glUniform4f(color_Location, 0.5f, 0.2f, 0.8f, 1.0f));

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    //shader.SetUniform4f("u_Color", 0.5f, 0.2f, 0.8f, 1.0f);


    Texture texture("res/tex/tex1.png", false);
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);


    /*Clear bindings.*/
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    float moveCam=0;
    float i = 0.05;
    while (!glfwWindowShouldClose(window)) 
    {
      glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
      glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(200, 100, 0));
      glm::vec3 rotationAxis(0, 0, 1);
      glm::mat4 modelRotation = glm::rotate(45.0f, rotationAxis);
      glm::mat4 modelScale = glm::scale(glm::vec3(2, 2, 1));

      glm::mat4 model = modelTranslate * modelRotation * modelScale;

      glm::mat4 mvp = proj * view * model;
      /*Render here*/
      /*(Abstracted to Renderer class)*/
      //GLCall(glClear(GL_COLOR_BUFFER_BIT));
      renderer.Clear();
      /*Using Vertices as a method to draw*/
      // glDrawArrays(GL_TRIANGLES, 0, 6);

      /*Shader bind.*/
      //GLCall(glUseProgram(shader));
      //GLCall(glUniform4f(color_Location, r, g, b, 1.0f));
      shader.Bind();
      shader.SetUniformMat4f("u_MVP", mvp);
      //shader.SetUniform4f("u_Color", 1.0, 0.0, 1.0, 1.0f);
      /*Vertex Array bind.*/
      //GLCall(glBindVertexArray(vao));
      // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
      renderer.Draw(va,ib,shader);

      /*Using Indices as a method to draw*/
      /*//(Abstracted to Renderer class)
      va.Bind();
      GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));*/

      /*Swap front and back buffers */
      glfwSwapBuffers(window);

      /*Poll for and process events */
      glfwPollEvents();


    }

    //GLCall(glDeleteProgram(shader));
  }
  glfwTerminate();

  return 0;
}