#pragma once

#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h> 

#include <iostream>
#include <fstream>
#include <glm.hpp>
#include <sstream>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	// activate the shader
	// ------------------------------------------------------------------------
	void Bind() const;
	void UnBind() const;
	unsigned int GetID() const { return ID; }

	// MVP
	unsigned int loc_model_matrix;
	unsigned int loc_view_matrix;
	unsigned int loc_projection_matrix;

	// utility uniform functions
	void SetVec4(const std::string& name, const::glm::vec4& value) const;
	void SetVec4(const std::string& name, float a, float b, float c, float d) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetValue(const std::string& name, float fValue) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
	void Init(const char* vertexPath, const char* fragmentPath);

	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void CheckCompileErrors(unsigned int shader, std::string type);
private:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	
};

