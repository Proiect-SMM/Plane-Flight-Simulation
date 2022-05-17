#pragma once

#include "Texture.h"
#include "Shader.h";
#include <vector>
#include <string>
struct Material {
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	float shininess;
	std::string name;
	int textureId;
};

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
	std::vector<glm::vec3> textureCoord;
	Material material;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void setupMesh();
public:

	Mesh() = default;
	Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, Material material);

	void Draw(Shader& shader);
};

