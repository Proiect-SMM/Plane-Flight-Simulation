#include "Pointlight.h"

Pointlight::Pointlight(const glm::vec3& pos) :
	position(pos)
{
	Projection = glm::ortho(-250.0f, 250.0f, -250.0f, 250.0f, near_plane, far_plane);
}

void Pointlight::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

glm::vec3 Pointlight::GetPosition()
{
	return position;
}

glm::mat4 Pointlight::ViewMatrix()
{
	return glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Pointlight::LightSpaceMatrix()
{
	return Projection * ViewMatrix();
}
