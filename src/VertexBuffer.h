#pragma once

class VertexBuffer {
 private:
  unsigned int m_RendererID;

 public:
  VertexBuffer(const int size, const void* data);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

};