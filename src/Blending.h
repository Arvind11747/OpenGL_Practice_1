#pragma once

class Blending 
{
private:
public:
	Blending();
	~Blending();

	void SetBlend(unsigned int src, unsigned int dest, unsigned int mode = GL_FUNC_ADD) const;
	void Bind() const;
	void Unbind() const;
};