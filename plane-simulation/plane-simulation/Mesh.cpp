#include "Mesh.h"
#include <string>

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture*> tex)
{
	vertices = vert;
	indices = ind;
	textures = tex;

	setupMesh();
}
