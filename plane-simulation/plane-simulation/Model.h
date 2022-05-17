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
private:
	std::vector<Mesh> meshes;
public:
	Model(const std::vector<Mesh>& meshess) : meshes(meshess) {}
	void Draw(Shader& shader);
};

