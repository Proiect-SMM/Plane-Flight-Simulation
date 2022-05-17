#pragma once
#include <vector>
#include <string>
#include "Camera.h"

class Skybox
{
private:
	unsigned int texture;
	unsigned int VAO, VBO, EBO;
public:
	Skybox();

	void Draw(Camera* camera);
};
