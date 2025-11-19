#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

    // === NUEVOS Getters y Setters ===
    glm::vec3 GetDirection() const { return direction; }
    void SetDirection(const glm::vec3& newDir) { direction = newDir; }

    // Facilita asignar todos los valores desde una interpolación
    void SetFrom(const DirectionalLight& other)
    {
        color = other.color;
        ambientIntensity = other.ambientIntensity;
        diffuseIntensity = other.diffuseIntensity;
        direction = other.direction;
    }

    ~DirectionalLight();


private:
	glm::vec3 direction;
};

