#include <GL/glew.h>

#include <iostream>

#include "GLErrorHandle.h"

void GLClearError() 
{
  while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) 
{
  while (GLenum error = glGetError()) 
  {
    std::cout << "[Open GL Error]: (" << error << ") --> Error in"
              << " function: " << function << " at Line: " << line << std::endl
              << "In File:" << file << std ::endl;
             
              
    return false;
  }
  return true;
}
