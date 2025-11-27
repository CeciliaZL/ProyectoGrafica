#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	controlcamara = 0;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	controlcamara = 0;
	animapuertas = false;
	controllibroML = false;
	luzrico = true; //luz rico proyecto 1
	luzcarl = true; //luz carl proyecto 1
	animprimo = false; //animación primo proyecto 1
	animjessie = false; //animación jessie proyecto 1
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final: Pucca x Mucha Lucha x Brawl Stars", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}


	if (key == GLFW_KEY_P && action == GLFW_PRESS) //ANIMACIÓN DE PUERTAS
	{
		theWindow->animapuertas = !theWindow->animapuertas;
	}




	if (key == GLFW_KEY_L && action == GLFW_PRESS) // ANIMACIÓN DE LIBRO
	{
		theWindow->controllibroML = !theWindow->controllibroML;

	}



	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		theWindow->controlcamara += 1;
		if (theWindow->controlcamara > 2)
			theWindow->controlcamara = 0;
	}

	//NUEVAS TECLAS PARA PROYECTO 1
	if (key == GLFW_KEY_I && action == GLFW_PRESS) // Luz rico proyecto 1
	{
		theWindow->luzrico = !theWindow->luzrico;
	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS) // Luz carl proyecto 1
	{
		theWindow->luzcarl = !theWindow->luzcarl;
	}

	if (key == GLFW_KEY_K && action == GLFW_PRESS) // Animacion primo proyecto 1
	{
		theWindow->animprimo = !theWindow->animprimo;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS) // Animacion jessie proyecto 1
	{
		theWindow->animjessie = !theWindow->animjessie;
	}
	//Fin nuevas teclas proyecto 1



	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;


	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}
void Window::setanimapuertas(bool value) {
	animapuertas = value;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
