#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "Shader.h"

struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureStorage
{
	unsigned int textureID;
	std::string type;
	std::string filePath;
};

class Mesh 
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<TextureStorage> m_textures;
	
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<TextureStorage>& textures);
	void Draw(Shader& shader) const;

private: 
	unsigned int m_VAO, m_VBO, m_IBO;
	
	void SetupMesh();
};