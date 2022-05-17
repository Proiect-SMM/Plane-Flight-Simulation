#pragma once
#include "Model.h"

#include "Mesh.h"
#include <vector>

class LoadObject
{
public:
	static Model LoadModel(const std::string& pathName);
};

