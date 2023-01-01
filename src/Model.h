#pragma once
#include "Shader.h"
#include <vector>

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(const char* filePath);
	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void LoadModel(const std::string& filePath);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<TextureStorage> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	
};