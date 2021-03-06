#pragma once
#include <iostream>
#include <glew.h>
#include <GLM.hpp>
#include <glfw3.h>

// necesare pentru citirea shader-elor
#include <stdlib.h> 
#include <stdio.h>
#include <math.h> 

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Airplane.h"

class Camera
{
public:
	enum class ECameraMovementType
	{
		UNKNOWN,
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

private:
	// Default camera values
	const float zNEAR = 0.1f;
	const float zFAR = 500.f;
	const float YAW = -90.0f;
	const float PITCH =-50.0f;
	const float FOV = 45.0f;
	glm::vec3 startPosition;

public:
	Camera(const int width, const int height, const glm::vec3& position);
	void Set(const int width, const int height, const glm::vec3& position);
	void Reset(const int width, const int height);
	void Reshape(int windowWidth, int windowHeight);
	const glm::vec3 GetPosition()const;
	
	const glm::mat4 GetViewMatrix() const;
	const glm::mat4 GetProjectionMatrix() const;
	void ProcessKeyboard(ECameraMovementType direction, float deltaTime);
	void MouseControl(float xPos, float yPos);
	void ProcessMouseScroll(float yOffset);
	void SetMode(const int& m);
	void BindAirplane(Airplane* airplane);


private:
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void UpdateCameraVectors();
	
protected:
	const float cameraSpeedFactor = 100.5f;
	const float mouseSensitivity = 0.1f;
	int mode = 0;
	// Perspective properties
	float zNear;
	float zFar;
	float FoVy;
	int width;
	int height;
	bool isPerspective;

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	// Euler Angles
	float yaw;
	float pitch;

	bool bFirstMouseMove = true;
	float lastX = 0.f, lastY = 0.f;
	Airplane* boundPlane = nullptr;
};

