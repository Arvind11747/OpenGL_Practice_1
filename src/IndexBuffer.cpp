#include <GL/glew.h>

#include "IndexBuffer.h"
#include "GLErrorHandle.h"


IndexBuffer::IndexBuffer(const int count, const unsigned int* data)
    : m_Count(count) 
{
    //Cautionary check!
  ASSERT(sizeof(unsigned int) == sizeof(GLuint)); 


  /* Generate Buffer*/
  GLCall(glGenBuffers(1, &m_RendererID));
  /* Bind that Buffer to a buffer binding object*/
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
  /*Creates a new data store for the buffer object currently bound to target
   * (GL_ARRAY_BUFFER).*/
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                      data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

void IndexBuffer::Bind() const{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
