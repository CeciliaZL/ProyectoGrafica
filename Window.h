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
	GLfloat getXChange();
	GLfloat getYChange();
	GLint getcontrolcamara() { return controlcamara; }
	GLboolean getcontrollibroML() { return controllibroML; }
	GLboolean getanimapuertas() { return animapuertas; }
	GLboolean getrico() { return luzrico; } // Luz rico proyecto 1
	GLboolean getcarl() { return luzcarl; } // Luz carl proyecto 1
	GLboolean getanimprimo() { return animprimo; } // Animación primo proyecto 1
	GLboolean getanimjessie() { return animjessie; } // Animación jessie proyecto 1

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	void setanimapuertas(bool value); //setter animapuertas
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLint controlcamara;
	GLboolean controllibroML;
	GLboolean animapuertas;
	GLboolean luzrico; // Luz rico proyecto 1
	GLboolean luzcarl; // Luz carl proyecto 1
	GLboolean animprimo; // Animación primo proyecto 1
	GLboolean animjessie; // Animación jessie proyecto 1

	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

