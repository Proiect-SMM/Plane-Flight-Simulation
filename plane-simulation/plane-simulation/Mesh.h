#pragma once

#include "Texture.h"
#include "Shader.h";
#include <vector>
#include <string>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};


class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textureCoord;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void setupMesh();
public:

	Mesh() = default;
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture*> tex);

	void Draw(const Shader* shader);
};

