#include "LoadObject.h"
#include "OBJ_Loader.h"
Model LoadObject::LoadModel(const std::string& pathName)
{
	std::vector<Mesh> meshes;

	// Initialize Loader
	objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile(pathName);

	// Check to see if it loaded

	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		std::vector<Material> materials;

		for (auto mat : Loader.LoadedMaterials)
		{
			Material temp;
			temp.Ka = glm::vec3(mat.Ka.X, mat.Ka.Y, mat.Ka.Z);
			temp.Kd = glm::vec3(mat.Kd.X, mat.Kd.Y, mat.Kd.Z);;
			temp.Ks = glm::vec3(mat.Ks.X, mat.Ks.Y, mat.Ks.Z);
			temp.shininess = mat.Ns;
			temp.name = mat.name;
			temp.textureId = Texture::CreateTexture(mat.map_Kd);
			materials.push_back(temp);
		}
		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			std::vector<Vertex> vertexes;
			std::vector<unsigned int> indices;
			std::vector<glm::vec3> textureCoord; 
			Material mat;
		    indices = Loader.LoadedMeshes[i].Indices;
			for (int j = 0; j < Loader.LoadedMeshes[i].Vertices.size(); j++)
			{
				Vertex temp;
				temp.Position = glm::vec3(Loader.LoadedMeshes[i].Vertices[j].Position.X,
					Loader.LoadedMeshes[i].Vertices[j].Position.Y,
					Loader.LoadedMeshes[i].Vertices[j].Position.Z);
				temp.Normal = glm::vec3(Loader.LoadedMeshes[i].Vertices[j].Normal.X,
					Loader.LoadedMeshes[i].Vertices[j].Normal.Y,
					Loader.LoadedMeshes[i].Vertices[j].Normal.Z);
				temp.TexCoords = glm::vec2(Loader.LoadedMeshes[i].Vertices[j].TextureCoordinate.X,
					Loader.LoadedMeshes[i].Vertices[j].TextureCoordinate.Y);
				vertexes.push_back(temp);
			}
			for (int k = 0; k < materials.size(); k++)
			{
				if (materials[k].name == Loader.LoadedMeshes[i].MeshMaterial.name)
					mat = materials[k];
			}
			Mesh constructedMesh = Mesh(vertexes, indices, mat);
			meshes.push_back(constructedMesh);
		}
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}
	return Model(meshes);
}
