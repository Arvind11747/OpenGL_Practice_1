#pragma once

#include <vector>
#include <stdexcept>
#include <GL/glew.h>
#include "GLErrorHandle.h"

struct VertexBufferElements {

  unsigned int type;
  unsigned int count;
  unsigned char normalised;

  static unsigned int GetSizeofType(unsigned int Type) {
    switch (Type) {
      case GL_FLOAT:            return sizeof(GLfloat);
      case GL_UNSIGNED_INT:     return sizeof(GLuint);
      case GL_UNSIGNED_BYTE:    return sizeof(GLbyte);
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout {
 private: 
     std::vector<VertexBufferElements> m_Elements;
     unsigned int m_stride;
 public:
     VertexBufferLayout() : m_stride(0){}
         
     template<typename T>
     void Push(unsigned int count) 
     {
       //static_assert(false); /*Doesn't work in VS2022 */
       std::runtime_error(false);
     }
          
     template<>
     void Push<float>(unsigned int count) {
         m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
         m_stride += count * VertexBufferElements::GetSizeofType(GL_FLOAT);
     }
     
     template<>
     void Push<unsigned int>(unsigned int count) {
         m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE}); 
         m_stride += count * VertexBufferElements::GetSizeofType(GL_UNSIGNED_INT);
     }
     
     template<>
     void Push<unsigned char>(unsigned int count) {
         m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE}); 
         m_stride += count * VertexBufferElements::GetSizeofType(GL_UNSIGNED_BYTE);
     }
     
     inline const std::vector<VertexBufferElements> GetElements() const& {return m_Elements;}
     inline unsigned int GetStride() const { return m_stride; }
};