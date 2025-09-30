#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getllantaD() { return llantaD; }
	GLfloat getchasis() { return chasis; }
	GLfloat getcofre() { return cofre; }

	float getPosAutoX() { return posAutoX; }
	float getPosAutoY() { return posAutoY; }
	float getPosAutoZ() { return posAutoZ; }
	void setPosAutoX(float val) { posAutoX = val; }
	void setPosAutoY(float val) { posAutoY = val; }
	void setPosAutoZ(float val) { posAutoZ = val; }



	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLfloat llantaD, chasis, cofre;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	float posAutoX = 0.0f;
	float posAutoY = 0.5f;
	float posAutoZ = 0.0f;
	
	bool mouseFirstMoved;
	void createCallbacks();
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
};
