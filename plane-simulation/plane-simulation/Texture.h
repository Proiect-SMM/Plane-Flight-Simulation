#pragma once
#include <glew.h>

#include <string>

class Texture
{
private:
	unsigned int id;
	std::string type;
	std::string fileName;
public:	
	Texture() = default;
	Texture(const std::string&);
	unsigned int GetID();
	void SetType(const std::string&);
	std::string GetType();
	std::string GetFileName();
	static unsigned int CreateTexture(const std::string& texturePath);
};