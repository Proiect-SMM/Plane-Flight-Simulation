#pragma once
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Pointlight
{
	glm::vec3 position = { 0,0,0 };

	float near_plane = 0.01f, far_plane = 500.0f;
	glm::mat4 Projection;
public:
	Pointlight() = default;
	Pointlight(const glm::vec3& pos);

	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition();

	glm::mat4 ViewMatrix();
	glm::mat4 LightSpaceMatrix();

};