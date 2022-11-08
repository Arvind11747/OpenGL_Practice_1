#include <GL/glew.h>

#include "GLErrorHandle.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const int size, const void* data) {
 
  /* Generate Buffer*/
  GLCall(glGenBuffers(1, &m_RendererID));
  /* Bind that Buffer to a buffer binding object*/
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  /*Creates a new data store for the buffer object currently bound to target
   * (GL_ARRAY_BUFFER).*/
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

void VertexBuffer::Bind() const{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
