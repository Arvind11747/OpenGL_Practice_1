#include "Mesh.h"
#include "GLErrorHandle.h"
#include "GL/glew.h"
#include <iostream>
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureStorage>& textures)
	: m_VAO(0),m_VBO(0), m_IBO(0)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;

	SetupMesh();
}

void Mesh::Draw(Shader& shader) const
{
	unsigned int diffuseN = 1;
	unsigned int specularN = 1;

	for (unsigned int i = 0; i < m_textures.size(); i++) 
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + i));

		std::string number;
		std::string name = m_textures[i].type;

		if(name=="texture_diffuse")
		{
			number = std::to_string(diffuseN++);
		}
		else if(name=="texture_specular")
		{
			number = std::to_string(specularN++);
		}
		shader.SetUniform1i(("material." + name + number).c_str(), i);
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textures[i].textureID));
	}
	GLCall(glActiveTexture(GL_TEXTURE0));

	GLCall(glBindVertexArray(m_VAO));
	GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0));
	GLCall(glBindVertexArray(0));



}

void Mesh::SetupMesh()
{
	GLCall(glGenVertexArrays(1, &m_VAO));
	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glGenBuffers(1, &m_IBO));

	GLCall(glBindVertexArray(m_VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,m_VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW));

	//positions
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));


	//normals
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal)));


	//tex coord
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)));

	GLCall(glBindVertexArray(0));
}
