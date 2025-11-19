#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	//Inicializaciones Cámara tercera persona
	distanceToTarget = 12.5f; // o el valor que estés usando
	offsetY = 10.0f;
	targetPosition = glm::vec3(0.0f);

	update();
}


void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::keyControlXZ(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += up * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= up * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}


void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

void Camera::mouseControlAvatar(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw -= xChange;     //invertir dirección horizontal
	pitch -= yChange;   // vertical queda igual

	if (pitch > 45.0f) pitch = 45.0f;
	if (pitch < -25.0f) pitch = -25.0f;

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}


GLfloat Camera::getYaw()
{
	return yaw;
}



void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


void Camera::followTarget(glm::vec3 targetPos, float targetYaw)
{
	targetPosition = targetPos;

	// Yaw total = yaw del avatar + rotación de cámara por mouse
	float combinedYaw = targetYaw + yaw;

	float yawRadians = glm::radians(combinedYaw);
	float pitchOffset = 10.0f;
	float pitchRadians = glm::radians(pitch + pitchOffset);
	offsetY = 2.0f;

	// Posición de la cámara en esfera (órbita)
	position.x = targetPos.x + sin(yawRadians) * cos(pitchRadians) * distanceToTarget;
	position.y = targetPos.y + sin(pitchRadians) * distanceToTarget + offsetY;
	position.z = targetPos.z + cos(yawRadians) * cos(pitchRadians) * distanceToTarget;


	// Dirección hacia el personaje
	front = glm::normalize(targetPos - position);

	// Recalcular up/right
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::controlAvatarMovement(bool* keys, GLfloat deltaTime, float& posX, float& posZ)
{
	// Dirección según yaw actual de la cámara
	float yawRad = glm::radians(yaw);
	glm::vec3 forwardDir = glm::normalize(glm::vec3(sin(yawRad), 0.0f, cos(yawRad)));
	glm::vec3 rightDir = glm::normalize(glm::cross(forwardDir, glm::vec3(0.0f, 1.0f, 0.0f)));

	float velocidad = 0.4f * deltaTime;
	avatarIsMoving = false;
	avatarMoveDirection = 0;

	// Movimiento relativo al yaw
	if (keys[GLFW_KEY_W])
	{
		posX -= forwardDir.x * velocidad;
		posZ -= forwardDir.z * velocidad;
		avatarIsMoving = true;
		avatarMoveDirection = 1; // adelante
	}
	if (keys[GLFW_KEY_S])
	{
		posX += forwardDir.x * velocidad;
		posZ += forwardDir.z * velocidad;
		avatarIsMoving = true;
		avatarMoveDirection = -1; // atrás
	}
	if (keys[GLFW_KEY_D])
	{
		posX -= rightDir.x * velocidad;
		posZ -= rightDir.z * velocidad;
		avatarIsMoving = true;
		avatarMoveDirection = 2; // derecha
	}
	if (keys[GLFW_KEY_A])
	{
		posX += rightDir.x * velocidad;
		posZ += rightDir.z * velocidad;
		avatarIsMoving = true;
		avatarMoveDirection = -2; // izquierda
	}
}





Camera::~Camera()
{
}
