#include <GL/glew.h>

#include "Blending.h"

#include "GLErrorHandle.h"
Blending::Blending()
{

}

Blending::~Blending()
{
}

void Blending::SetBlend(unsigned int src, unsigned int dest, unsigned int mode) const
{
	GLCall(glBlendFunc(src, dest));
	GLCall(glBlendEquation(mode));
}

void Blending::Bind() const
{
	GLCall(glEnable(GL_BLEND));
}

void Blending::Unbind() const
{
	GLCall(glDisable(GL_BLEND));
}
