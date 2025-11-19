#pragma once

#include <glew.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);

	~Light();

	// === Getters ===
	glm::vec3 GetColor() const { return color; }
	GLfloat GetAmbientIntensity() const { return ambientIntensity; }
	GLfloat GetDiffuseIntensity() const { return diffuseIntensity; }

	// === Setters ===
	void SetColor(const glm::vec3& newColor) { color = newColor; }
	void SetAmbientIntensity(GLfloat intensity) { ambientIntensity = intensity; }
	void SetDiffuseIntensity(GLfloat intensity) { diffuseIntensity = intensity; }

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

