#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "Matrix.h"

namespace Inputs
{
class Controls
{
public:
	Controls(void);
	~Controls(void);

public:
	//static void ComputeMatrices(Maths::Matrix& projectionMatrix, Maths::Matrix& viewMatrix);

public: // getters and setters
	glm::vec3 GetPosition() const { return _position; };
	float GetHorizontalAngle() const { return _horizontalAngle; };
	float GetVerticalAngle() const { return _verticalAngle; };
	float GetFoV() const { return _fov; };
	float GetAspect() const { return _aspect; };
	float GetZNear() const { return _zNear; };
	float GetZFar() const { return _zFar; };
	float GetSpeed() const { return _speed; };
	float GetMouseSpeed() const { return _mouseSpeed; };
private:
	glm::vec3 _position; // Initial position : on +Z
	float _horizontalAngle; // Initial horizontal angle : toward -Z
	float _verticalAngle; // Initial vertical angle : none

	float _fov;
	float _aspect;
	float _zNear;
	float _zFar;

	float _speed;
	float _mouseSpeed;
};
}

