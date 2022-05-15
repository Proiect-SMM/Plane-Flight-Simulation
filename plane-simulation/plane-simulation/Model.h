#pragma once

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Texture.h"
#include "Mesh.h"



class Model {
public:
	Model(char* path)
	{
		loadModel(path);
	}
	void Draw(Shader* shader);
private:
	std::vector<Mesh*> meshes;
	std::string directory;
	std::vector<Texture*> textures_loaded;

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

