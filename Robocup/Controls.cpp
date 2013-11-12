#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Controls.h"


Inputs::Controls::Controls(void) :
	_position(glm::vec3(0, 0, 5)),
	_horizontalAngle(3.14f),
	_verticalAngle(0.0f),
	_fov(45.0f),
	_aspect(4.0f / 3.0f),
	_zNear(0.1f),
	_zFar(100.0f),
	_speed(3.0f),	// 3 units / second
	_mouseSpeed(0.005f)
{
}


Inputs::Controls::~Controls(void)
{
}


//void Inputs::Controls::ComputeMatrices()
//{
//	// glfwGetTime is called only once, the first time this function is called
//	static double lastTime = glfwGetTime();
//
//	// Compute time difference between current and last frame
//	double currentTime = glfwGetTime();
//	float deltaTime = float(currentTime - lastTime);
//
//	// Get mouse position
//	int xpos, ypos;
//	glfwGetMousePos(&xpos, &ypos);
//
//	// Reset mouse position for next frame
//	glfwSetMousePos(1024/2, 768/2);
//
//	// Compute new orientation
//	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
//	verticalAngle   += mouseSpeed * float( 768/2 - ypos );
//
//	// Direction : Spherical coordinates to Cartesian coordinates conversion
//	glm::vec3 direction(
//		cos(verticalAngle) * sin(horizontalAngle), 
//		sin(verticalAngle),
//		cos(verticalAngle) * cos(horizontalAngle)
//	);
//	
//	// Right vector
//	glm::vec3 right = glm::vec3(
//		sin(horizontalAngle - 3.14f/2.0f), 
//		0,
//		cos(horizontalAngle - 3.14f/2.0f)
//	);
//	
//	// Up vector
//	glm::vec3 up = glm::cross( right, direction );
//
//	// Move forward
//	if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
//		position += direction * deltaTime * speed;
//	}
//	// Move backward
//	if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
//		position -= direction * deltaTime * speed;
//	}
//	// Strafe right
//	if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
//		position += right * deltaTime * speed;
//	}
//	// Strafe left
//	if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
//		position -= right * deltaTime * speed;
//	}
//
//	float FoV = initialFoV - 5 * glfwGetMouseWheel();
//
//	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
//	// Camera matrix
//	ViewMatrix       = glm::lookAt(
//								position,           // Camera is here
//								position+direction, // and looks here : at the same position, plus "direction"
//								up                  // Head is up (set to 0,-1,0 to look upside-down)
//						   );
//
//	// For the next frame, the "last time" will be "now"
//	lastTime = currentTime;
//}