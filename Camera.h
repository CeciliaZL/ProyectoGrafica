#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void keyControlXZ(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	void mouseControlAvatar(GLfloat xChange, GLfloat yChange);

	GLfloat getYaw();

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();




	glm::vec3 getFront() { return front; }
	glm::vec3 getRight() { return right; }
	glm::vec3 getUp() { return up; }

	bool isAvatarMoving() const { return avatarIsMoving; }

	void followTarget(glm::vec3 targetPos, float targetYaw);
	void controlAvatarMovement(bool* keys, GLfloat deltaTime, float& posX, float& posZ);

	int getAvatarMoveDirection() const { return avatarMoveDirection; }


	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;
	bool avatarIsMoving; // indica si el personaje está caminando

	// ==== Tercera Persona ====
	GLfloat distanceToTarget; // Distancia detrás del personaje
	GLfloat offsetY;          // Altura respecto al personaje
	glm::vec3 targetPosition; // Posición del personaje (avatar)
	int avatarMoveDirection;
	// 0 = quieto, 1 = adelante, -1 = atrás, 2 = derecha, -2 = izquierda


	void update();
};

