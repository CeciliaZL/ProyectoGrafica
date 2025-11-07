/*
PROYECTO FINAL
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera1;
Camera camera2;
Camera camera3;

Texture pisoTexture;
Texture plainTexture;

//========================Declaración de Modelos===================================

//************************** DANIEL ***********************************************

Model PiramideSol_M;

Model BuenaNina_M;
Model ElFundadorCuadro_M;
//Frijolito
Model FrijolitoHeadBody_M;
Model FrijolitoRightHand_M;
Model FrijolitoLeftHand_M;
Model FrijolitoRightLeg_M;
Model FrijolitoLeftLeg_M;


Model GaruHeadBody;
Model GaruLeftHand;
Model GaruRightHand;
Model GaruLeftLeg;
Model GaruRightLeg;

Model MuchaLuchaLibro_M;
Model MuchaLuchaLibroPedestal_M;

Model PuccaHeadBody;
Model PuccaLeftHand;
Model PuccaRightHand;
Model PuccaLeftLeg;
Model PuccaRightLeg;

Model PuccaHeart;

Model Ricochet_M;
Model Terciopelo_M;


//********************************** CECILIA ******************************************************

//************************************* AXEL ******************************************************




//=================================== FIN Declaración de Modelos===================================


// ================================== Declaración Skyboxes ========================================

Skybox skybox1;
Skybox skybox2;
Skybox skybox3;
Skybox skybox4;

//Controlar tiempo y Skybox Activo

GLfloat startTime = glfwGetTime();
int currentSkybox = 0;  // 0 = skybox1 AMANECER, 1 = skybox2 MEDIODIA, 2 = skybox3 ATARDECER, 3 = skybox4 NOCHE
float changeInterval = 300.0;  // tiempo en segundos
int totalSkyboxes = 4;
// ========================================= Fin Skyboxes =========================================


// ============================================ MATERIALES ========================================
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//Variables de control de tiempo de Skybox


//=========================================== LUCES ================================================
// MAINLIGHT DIRECCIONAL
DirectionalLight mainLightamanecer;
DirectionalLight mainLightdia;
DirectionalLight mainLightatardecer;
DirectionalLight mainLightnoche;

//SPOTLIGHT

//POINTLIGHT



PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

//=========================================== FIN LUCES ================================================

//=========================================== DECLARACION VARIABLES DE ANIMACION ================================================

//Animacion ajolote
float ajoloteAvance = 0.0f;     // movimiento base (como el dragonavance)
float anguloAjolote = 0.0f;     // ángulo que usaremos para el seno
float velocidadAjolote = 5.0f;

//=============Animación Pucca===========================

// ---- Movimiento Pucca ----
float puccaPosX = 15.0f;
float puccaPosY = 1.8f;
float puccaPosZ = 60.0f; //IMPORTANTE: SEPARACIÓN PUCCA DE GARU
float puccaRotY = 180.0f; // mirando hacia -Z

float puccaSpeed = 0.5f;
int puccaState = 0;

float puccaTargetX = 15.0f;
float puccaTargetZ = -160.0f;

// ---- Animación de caminata Pucca ----
bool puccaIsWalking = true;
float puccaWalkTime = 0.0f;
float puccaArmAmplitude = 25.0f;
float puccaLegAmplitude = 15.0f;
float puccaWalkSpeed = 0.25f;

float puccaRightArmAngle = 0.0f;
float puccaLeftArmAngle = 0.0f;
float puccaRightLegAngle = 0.0f;
float puccaLeftLegAngle = 0.0f;

//Corazones de Pucca
float puccaHeartFloatTime = 0.0f;   // tiempo acumulado para la animación
float puccaHeartFloatSpeed = 0.1f;  // velocidad del flote
float puccaHeartFloatAmplitude = 0.8f; // altura máxima del flote
float puccaHeartOffsetY = 0.0f;



//=================Animación Garu===========================

// ---- Movimiento Garu ----
float garuPosX = 15.0f;
float garuPosY = 1.8f;
float garuPosZ = -30.0f;     // posición inicial 

float garuRotY = 180.0f;     // mirando hacia -Z

float garuSpeed = 0.5f;
int garuState = 0;

float garuTargetX = 15.0f;
float garuTargetZ = garuPosZ - 130.0f;  // primer objetivo relativo

// ---- Animación de caminata Garu ----
bool garuIsWalking = true;
float garuWalkTime = 0.0f;
float garuArmAmplitude = 25.0f;
float garuLegAmplitude = 15.0f;
float garuWalkSpeed = 0.25f;

float garuRightArmAngle = 0.0f;
float garuLeftArmAngle = 0.0f;
float garuRightLegAngle = 0.0f;
float garuLeftLegAngle = 0.0f;


//=================Animación Libro===========================

float libroML_posY = 4.45f;
float libroML_targetY = 6.70f;
float libroML_speedY = 0.05f;

float libroML_angleZ = 0.0f;
float libroML_targetAngleZ = -45.0f;
float libroML_speedRotZ = 1.0f;

float libroML_posX = 0.0f;
float libroML_targetX = -8.0f;
float libroML_speedX = 0.125f;

float libroML_offsetY = 0.0f;
float libroML_targetOffsetY = -24.0f;
float libroML_speedDown = 0.25f;

float libroML_angleY = 0.0f;
float libroML_targetAngleY = 360.0f;
float libroML_speedRotY = 1.25f;

int   libroML_stage = 0;;
bool libroML_return = false;

//======================================= FIN DECLARACION VARIABLES DE ANIMACION ================================================

Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,

	};

	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		1.f,	1.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	1.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,	1.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	-1.0f,	0.0f,

	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCubo();
	CreateShaders();

	camera1 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, -15.0f, 1.0f, 0.5f);
	camera2 = Camera(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f, 1.0f, 0.5f);
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	// ================================ TEXTURAS ==========================================

	pisoTexture = Texture("Textures/pisopf.png");
	pisoTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();


	// ================================= CARGA DE MODELOS ===============================

	// ******************************** DANIEL ********************************************

	BuenaNina_M = Model();
	BuenaNina_M.LoadModel("Models/BuenaNina.obj");

	FrijolitoHeadBody_M = Model();
	FrijolitoHeadBody_M.LoadModel("Models/FrijolitoHeadBody.obj");


	FrijolitoLeftHand_M = Model();
	FrijolitoLeftHand_M.LoadModel("Models/FrijolitoLeftHand.obj");

	FrijolitoRightHand_M = Model();
	FrijolitoRightHand_M.LoadModel("Models/FrijolitoRightHand.obj");

	FrijolitoLeftLeg_M = Model();
	FrijolitoLeftLeg_M.LoadModel("Models/FrijolitoLeftLeg.obj");

	FrijolitoRightLeg_M = Model();
	FrijolitoRightLeg_M.LoadModel("Models/FrijolitoRightLeg.obj");

	ElFundadorCuadro_M = Model();
	ElFundadorCuadro_M.LoadModel("Models/elfundador_cuadro.obj");

	GaruHeadBody = Model();
	GaruHeadBody.LoadModel("Models/GaruCuerpo.obj");

	GaruLeftHand = Model();
	GaruLeftHand.LoadModel("Models/GaruLeftHand.obj");

	GaruRightHand = Model();
	GaruRightHand.LoadModel("Models/GaruRightHand.obj");

	GaruLeftLeg = Model();
	GaruLeftLeg.LoadModel("Models/GaruLeftLeg.obj");

	GaruRightLeg = Model();
	GaruRightLeg.LoadModel("Models/GaruRightLeg.obj");

	MuchaLuchaLibro_M = Model();
	MuchaLuchaLibro_M.LoadModel("Models/MuchaLuchaLibro.obj");

	MuchaLuchaLibroPedestal_M = Model();
	MuchaLuchaLibroPedestal_M.LoadModel("Models/PedestalLibro.obj");

	PiramideSol_M = Model();
	PiramideSol_M.LoadModel("Models/PiramideSol.obj");

	PuccaHeart = Model();
	PuccaHeart.LoadModel("Models/PuccaHeart.obj");

	PuccaHeadBody = Model();
	PuccaHeadBody.LoadModel("Models/PuccaCuerpo.obj");

	PuccaLeftHand = Model();
	PuccaLeftHand.LoadModel("Models/PuccaLeftHand.obj");

	PuccaRightHand = Model();
	PuccaRightHand.LoadModel("Models/PuccaRightHand.obj");

	PuccaLeftLeg = Model();
	PuccaLeftLeg.LoadModel("Models/PuccaLeftLeg.obj");

	PuccaRightLeg = Model();
	PuccaRightLeg.LoadModel("Models/PuccaRightLeg.obj");

	Ricochet_M = Model();
	Ricochet_M.LoadModel("Models/RicochetPersonaje.obj");

	Terciopelo_M = Model();
	Terciopelo_M.LoadModel("Models/terciopelo.obj");


	// ******************************** CECILIA ********************************************


	// ================================= FIN CARGA DE MODELOS ===============================
	
	// ================================= CREACION Y CARGA DE SKYBOXES ===============================
	// --- Skybox 1 ---
	std::vector<std::string> skyboxFaces1 = {
		"Textures/Skybox/skybox-amanecer_rt.png",
		"Textures/Skybox/skybox-amanecer_lf.png",
		"Textures/Skybox/skybox-amanecer_dn.png",
		"Textures/Skybox/skybox-amanecer_up.png",
		"Textures/Skybox/skybox-amanecer_bk.png",
		"Textures/Skybox/skybox-amanecer_ft.png"
	};

	// --- Skybox 2 ---
	std::vector<std::string> skyboxFaces2 = {
		"Textures/Skybox/skybox-dia_rt.png",
		"Textures/Skybox/skybox-dia_lf.png",
		"Textures/Skybox/skybox-dia_dn.png",
		"Textures/Skybox/skybox-dia_up.png",
		"Textures/Skybox/skybox-dia_bk.png",
		"Textures/Skybox/skybox-dia_ft.png"
	};

	// --- Skybox 3 ---
	std::vector<std::string> skyboxFaces3 = {
		"Textures/Skybox/skybox-atardecer_rt.png",
		"Textures/Skybox/skybox-atardecer_lf.png",
		"Textures/Skybox/skybox-atardecer_dn.png",
		"Textures/Skybox/skybox-atardecer_up.png",
		"Textures/Skybox/skybox-atardecer_bk.png",
		"Textures/Skybox/skybox-atardecer_ft.png"
	};

	// --- Skybox 4 ---
	std::vector<std::string> skyboxFaces4 = {
		"Textures/Skybox/skybox-noche_rt.png",
		"Textures/Skybox/skybox-noche_lf.png",
		"Textures/Skybox/skybox-noche_dn.png",
		"Textures/Skybox/skybox-noche_up.png",
		"Textures/Skybox/skybox-noche_bk.png",
		"Textures/Skybox/skybox-noche_ft.png"
	};

	// Crear los cuatro objetos Skybox
	Skybox skybox1(skyboxFaces1);
	Skybox skybox2(skyboxFaces2);
	Skybox skybox3(skyboxFaces3);
	Skybox skybox4(skyboxFaces4);

	// ================================= FIN SKYBOXES ===============================

	// ================================= MATERIALES =================================

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);
	// ================================= FIN MATERIALES =================================

	// ================================= LUCES ===========================================
	
	// MAINLIGHT DIRECCIONAL

	mainLightamanecer = DirectionalLight(
		1.0f, 1.0f, 1.0f,   // color blanco
		0.5f, 0.6f,         // intensidades (ambiental baja, difusa moderada)
		-1.0f, -0.3f, -0.2f // dirección (sol bajo, inclinado)
	);

	mainLightdia = DirectionalLight(
		0.95f, 0.95f, 0.9f,  // blanco más neutro, menos saturado
		0.6f, 0.7f,         // intensidades ligeramente reducidas
		0.0f, -1.0f, 0.0f    // dirección del sol cenital
	);

	mainLightatardecer = DirectionalLight(
		0.9f, 0.75f, 0.65f,  // color más claro y menos rojizo (tono dorado suave)
		0.5f, 0.7f,          // intensidades un poco más altas (más brillo general)
		1.0f, -0.3f, -0.2f    // dirección del sol bajo en el horizonte
	);

	mainLightnoche = DirectionalLight(
		0.094f, 0.235f, 0.235f, // color azul verdoso oscuro (#183C3C)
		0.15f, 0.30f,         // intensidades más altas (aumenta la visibilidad nocturna)
		0.0f, -1.0f, 0.0f      // dirección ligeramente diagonal
	);

	//POINTLIFGHT
	//contador de luces puntuales

	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;



	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;


	//SPOTLIGHT

	//luz fija
	//spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
	//	1.0f, 2.0f,
	//	0.0f, 10.0f, 0.0f,
	//	0.0f, -5.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	15.0f);
	//spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 

	

	// ================================= FIN LUCES ===========================================

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader


	//=========================================== DECLARACION MATRICES ================================================

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);

	//FRIJOLITO
	glm::vec3 avatarPos;
	glm::mat4 modelauxfrijolito(1.0);

	//PUCCA
	glm::mat4 puccaModelBase(1.0);
	
	//GARU
	glm::mat4 garuModelBase(1.0);

	//LIBRO CODIGO DE LA LUCHA LIBRO ENMASCARADA
	glm::mat4 libroMLModelBase(1.0);
	glm::vec3 libroML_pivot(1.0);
	glm::mat4 libroML_rotGlobalY(1.0);

	//COLOR
	glm::vec3 color(1.0);


	glm::mat4 view;
	glm::vec3 eyePos;


	glm::vec3 lowerLight;


	//=========================================== FIN DECLARACION MATRICES ================================================






	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();

		// ========================================== CONTROL DE CAMARAS =============================================
		if (mainWindow.getcontrolcamara() == 0)
		{
			// Cámara 1 - Tercera Persona
			camera1.keyControl(mainWindow.getsKeys(), deltaTime);
			camera1.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			view = camera1.calculateViewMatrix();
			eyePos = camera1.getCameraPosition();
		}
		else if (mainWindow.getcontrolcamara() == 1)
		{
			// Cámara aérea
			camera2.keyControlXZ(mainWindow.getsKeys(), deltaTime);
			view = camera2.calculateViewMatrix();
			eyePos = camera2.getCameraPosition();
		}
		else if (mainWindow.getcontrolcamara() == 2)
		{
			// Cámara 3 - Libre
			camera3.keyControl(mainWindow.getsKeys(), deltaTime);
			camera3.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			view = camera3.calculateViewMatrix();
			eyePos = camera3.getCameraPosition();
		}

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Cambiar skybox cada x segundos
		if (now - startTime >= changeInterval) {
			currentSkybox = (currentSkybox + 1) % totalSkyboxes;  // Cicla entre 0–3
			startTime = now;
		}


		// ===== Dibujar skybox según currentSkybox =====
		switch (currentSkybox)
		{
		case 0:
			skybox1.DrawSkybox(view, projection);
			break;
		case 1:
			skybox2.DrawSkybox(view, projection);
			break;
		case 2:
			skybox3.DrawSkybox(view, projection);
			break;
		case 3:
			skybox4.DrawSkybox(view, projection);
			break;
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		// ================================ Actualizar uniforms ==================================================
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(uniformEyePosition, eyePos.x, eyePos.y, eyePos.z);


		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		lowerLight = camera1.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera1.getCameraDirection());

		//==================CONTROL DE LA LUZ MAINLIGHT DE ACUERDO AL SKYBOX ================================

		switch (currentSkybox) {
		case 0:
			shaderList[0].SetDirectionalLight(&mainLightamanecer);
			break;
		case 1:
			shaderList[0].SetDirectionalLight(&mainLightdia);
			break;
		case 2:
			shaderList[0].SetDirectionalLight(&mainLightatardecer);
			break;
		case 3:

			shaderList[0].SetDirectionalLight(&mainLightnoche);
			break;
		}



		//información al shader de fuentes de iluminación
		//shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);







		// =========================== RENDERIZADO, ANIMACIÓN Y TEXTURIZADO DE MODELOS Y GEOMETRÍAS =========================

		// ======================================== PISO CROQUIS ============================================================

		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f * 0.788f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		// ************************************* AVATAR ***********************************************
		// ********************************************************************************************
		// ********************************************************************************************


		avatarPos = camera1.getCameraPosition(); 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.865f, -5.0f)); //+5.0
		//model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f)); 
		modelauxfrijolito = model;

		// Cuerpo Cabeza
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess); 
		FrijolitoHeadBody_M.RenderModel();

		// Brazo derecho
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(garuRightArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoRightHand_M.RenderModel();

		// Brazo izquierdo
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(garuLeftArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoLeftHand_M.RenderModel();

		// Pierna derecha
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(garuRightLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoRightLeg_M.RenderModel();

		// Pierna izquierda
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(garuLeftLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoLeftLeg_M.RenderModel();

		// ************************************* FIN AVATAR *******************************************
		// ********************************************************************************************
		// ********************************************************************************************




		//CREANDO LA CABINA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, -4.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(5.0f, 3.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		plainTexture.UseTexture();
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[4]->RenderMesh();

		//ARTICULACION1 CABINA-BRAZO
		//model = glm::mat4(1.0);//NO EXISTE, SUSTITUIRLA POR:
		model = modelaux;
		model = glm::rotate(model, glm::radians(mainWindow.getmuevex()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		sp.render();

		// Creando el brazo de una grúa
		//articulacion1 hasta articulación5 sólo son puntos de rotación o articulación, en este caso no dibujaremos esferas que los representen

		//primer brazo que conecta con la cabina
		//para reiniciar la matriz de modelo con valor de la matriz identidad
		//model = glm::mat4(1.0);
		//rotación alrededor de la articulación que une con la cabina
		model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		//Traslación inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		modelaux = model;
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh();
		//meshList[3]->RenderMeshGeometry(); //dibuja las figuras geométricas cilindro, cono, pirámide base cuadrangular
		//sp.render(); //dibuja esfera

		//SEGUNDA ARTICULACION 
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueveavatarx()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		sp.render(); //dibuja esfera

		//segundo brazo

		//para reiniciar la matriz de modelo con valor de la matriz identidad
		//Comentar y se modifica para agregar la jerarquia:
		//usar una matriz temporal o auxiliar

		//model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));

		//Traslación inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		//model = glm::translate(model, glm::vec3(-0.30f, 5.6f, 0.0f));
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 5.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh(); //dibuja cubo y pirámide triangular

		//TERCER ARTICULACION
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getmueveavatarz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		sp.render(); //dibuja esfera

		//TERCER BRAZO
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // 135-90 = 45 grados
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 5.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh(); //dibuja cubo y pirámide triangular


		model = glm::translate(model, glm::vec3(0.0f, .5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 5.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh(); //dibuja cubo y pirámide triangular



		//===================================== Ricochet =======================================

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.865f, 0.0f)); //+5.0
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ricochet_M.RenderModel();

		//===================================== Buena Niña =======================================

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.865f, 5.0f)); //+5.0
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BuenaNina_M.RenderModel();

		//=====================================================GARU==============================



		switch (garuState)
		{
		case 0: // avanzar primer tramo Z
			garuRotY = 0.0f; // mirar hacia -Z
			if (garuPosZ > garuTargetZ) {
				garuPosZ -= garuSpeed * deltaTime;
				if (garuPosZ <= garuTargetZ) {
					garuPosZ = garuTargetZ;
					garuState = 1;
				}
			}
			break;

		case 1: // giro hacia -X
			garuRotY = 90.0f;
			garuTargetX = garuPosX - 52.5f;
			garuState = 2;
			break;

		case 2: // avanzar 52.5 hacia -X
			if (garuPosX > garuTargetX) {
				garuPosX -= garuSpeed * deltaTime;
				if (garuPosX <= garuTargetX) {
					garuPosX = garuTargetX;
					garuState = 3;
				}
			}
			break;

		case 3: // giro hacia +Z
			garuRotY = 180.0f;
			garuTargetZ = garuPosZ + 320.0f;
			garuState = 4;
			break;

		case 4: // avanzar 320 hacia +Z
			if (garuPosZ < garuTargetZ) {
				garuPosZ += garuSpeed * deltaTime;
				if (garuPosZ >= garuTargetZ) {
					garuPosZ = garuTargetZ;
					garuState = 5;
				}
			}
			break;

		case 5: // giro hacia +X
			garuRotY = 270.0f;
			garuTargetX = garuPosX + 52.5f;
			garuState = 6;
			break;

		case 6: // avanzar 52.5 hacia +X
			if (garuPosX < garuTargetX) {
				garuPosX += garuSpeed * deltaTime;
				if (garuPosX >= garuTargetX) {
					garuPosX = garuTargetX;
					garuState = 7;
				}
			}
			break;

		case 7: // giro hacia -Z
			garuRotY = 0.0f;
			garuTargetZ = garuPosZ - 160.0f;
			garuState = 8;
			break;

		case 8: // avanzar 160 hacia -Z
			if (garuPosZ > garuTargetZ) {
				garuPosZ -= garuSpeed * deltaTime;
				if (garuPosZ <= garuTargetZ) {
					garuPosZ = garuTargetZ;
					garuState = 9;
				}
			}
			break;

		case 9: // reiniciar ciclo
			garuState = 0;
			garuTargetZ = garuPosZ - 160.0f; // nuevo primer tramo relativo
			break;
		}


		// Determinar si Garu está caminando
		garuIsWalking = !(fabs(garuPosX - garuTargetX) < 0.05f && fabs(garuPosZ - garuTargetZ) < 0.05f);

		if (garuIsWalking)
		{
			garuWalkTime += deltaTime * garuWalkSpeed;

			garuRightArmAngle = sin(garuWalkTime + 3.14f) * garuArmAmplitude; // opuesto
			garuLeftArmAngle = sin(garuWalkTime) * garuArmAmplitude;
			garuRightLegAngle = sin(garuWalkTime) * garuLegAmplitude;
			garuLeftLegAngle = sin(garuWalkTime + 3.14f) * garuLegAmplitude; // opuesto
		}
		else
		{
			garuRightArmAngle = garuLeftArmAngle = 0.0f;
			garuRightLegAngle = garuLeftLegAngle = 0.0f;
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(garuPosX, garuPosY, garuPosZ));
		model = glm::rotate(model, glm::radians(garuRotY), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(1.15f));

		garuModelBase = model;

		// Cuerpo
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GaruHeadBody.RenderModel();

		// Brazo derecho
		model = garuModelBase;
		model = glm::rotate(model, glm::radians(garuRightArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GaruRightHand.RenderModel();

		// Brazo izquierdo
		model = garuModelBase;
		model = glm::rotate(model, glm::radians(garuLeftArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GaruLeftHand.RenderModel();

		// Pierna derecha
		model = garuModelBase;
		model = glm::rotate(model, glm::radians(garuRightLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GaruRightLeg.RenderModel();

		// Pierna izquierda
		model = garuModelBase;
		model = glm::rotate(model, glm::radians(garuLeftLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GaruLeftLeg.RenderModel();

		//==================================  FIN GARU    =========================


		//===============================     PUCCA  =================================

		//ANIMACION PUCCA 


		switch (puccaState)
		{
		case 0: // avanzar hacia -160 en Z
			puccaRotY = 0.0f; // mirar hacia -Z
			if (puccaPosZ > puccaTargetZ) {
				puccaPosZ -= puccaSpeed * deltaTime;
				if (puccaPosZ <= puccaTargetZ) {
					puccaPosZ = puccaTargetZ;
					puccaState = 1;
				}
			}
			break;

		case 1: // giro hacia -X
			puccaRotY = 90.0f;
			puccaTargetX = puccaPosX - 52.5f;
			puccaState = 2;
			break;

		case 2: // avanzar 52.5 hacia -X
			if (puccaPosX > puccaTargetX) {
				puccaPosX -= puccaSpeed * deltaTime;
				if (puccaPosX <= puccaTargetX) {
					puccaPosX = puccaTargetX;
					puccaState = 3;
				}
			}
			break;

		case 3: // giro hacia +Z
			puccaRotY = 180.0f;
			puccaTargetZ = puccaPosZ + 320.0f;
			puccaState = 4;
			break;

		case 4: // avanzar 320 hacia +Z
			if (puccaPosZ < puccaTargetZ) {
				puccaPosZ += puccaSpeed * deltaTime;
				if (puccaPosZ >= puccaTargetZ) {
					puccaPosZ = puccaTargetZ;
					puccaState = 5;
				}
			}
			break;

		case 5: // giro hacia +X
			puccaRotY = 270.0f;
			puccaTargetX = puccaPosX + 52.5f;
			puccaState = 6;
			break;

		case 6: // avanzar 52.5 hacia +X
			if (puccaPosX < puccaTargetX) {
				puccaPosX += puccaSpeed * deltaTime;
				if (puccaPosX >= puccaTargetX) {
					puccaPosX = puccaTargetX;
					puccaState = 7;
				}
			}
			break;

		case 7: // giro hacia -Z
			puccaRotY = 0.0f;
			puccaTargetZ = puccaPosZ - 160.0f;
			puccaState = 8;
			break;

		case 8: // avanzar 160 hacia -Z
			if (puccaPosZ > puccaTargetZ) {
				puccaPosZ -= puccaSpeed * deltaTime;
				if (puccaPosZ <= puccaTargetZ) {
					puccaPosZ = puccaTargetZ;
					puccaState = 9;
				}
			}
			break;

		case 9: // reiniciar ciclo
			puccaState = 0;

			// *No reiniciamos posición*, solo calculamos el siguiente objetivo
			puccaTargetZ = puccaPosZ - 160.0f;
			break;
		}


		// Si se está moviendo, animar caminata
		puccaIsWalking = !(fabs(puccaPosX - puccaTargetX) < 0.05f && fabs(puccaPosZ - puccaTargetZ) < 0.05f);

		if (puccaIsWalking)
		{
			puccaWalkTime += deltaTime * puccaWalkSpeed;

			puccaRightArmAngle = sin(puccaWalkTime + 3.14f) * puccaArmAmplitude; 
			puccaLeftArmAngle = sin(puccaWalkTime) * puccaArmAmplitude;

			puccaRightLegAngle = sin(puccaWalkTime) * puccaLegAmplitude;
			puccaLeftLegAngle = sin(puccaWalkTime + 3.14f) * puccaLegAmplitude;
		}
		else
		{
			// está quieta: brazos y piernas relax
			puccaRightArmAngle = puccaLeftArmAngle = 0.0f;
			puccaRightLegAngle = puccaLeftLegAngle = 0.0f;
		}




		// ---------- Cuerpo principal ----------
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(puccaPosX, puccaPosY, puccaPosZ));
		model = glm::rotate(model, glm::radians(puccaRotY), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(1.15f));

		puccaModelBase = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaHeadBody.RenderModel();

		// ---------- Right Hand ----------
		model = puccaModelBase;
		model = glm::rotate(model, glm::radians(puccaRightArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaRightHand.RenderModel();

		// ---------- Left Hand ----------
		model = puccaModelBase;
		model = glm::rotate(model, glm::radians(puccaLeftArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaLeftHand.RenderModel();

		// ---------- Right Leg ----------
		model = puccaModelBase;
		model = glm::rotate(model, glm::radians(puccaRightLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaRightLeg.RenderModel();

		// ---------- Left Leg ----------
		model = puccaModelBase;
		model = glm::rotate(model, glm::radians(puccaLeftLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaLeftLeg.RenderModel();

		//Corazones

		// Actualizar tiempo
		puccaHeartFloatTime += deltaTime * puccaHeartFloatSpeed;

		// Calcular desplazamiento vertical con seno
		puccaHeartOffsetY = sin(puccaHeartFloatTime) * puccaHeartFloatAmplitude;


		model = puccaModelBase;
		// Posición base del corazón + desplazamiento vertical
		model = glm::translate(model, glm::vec3(2.0f, 1.0f + puccaHeartOffsetY, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaHeart.RenderModel();

		model = puccaModelBase;
		// Posición base del corazón + desplazamiento vertical
		model = glm::translate(model, glm::vec3(-2.0f, 2.0f + puccaHeartOffsetY, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaHeart.RenderModel();

		model = puccaModelBase;
		// Posición base del corazón + desplazamiento vertical
		model = glm::translate(model, glm::vec3(0.5f, 3.0f + puccaHeartOffsetY, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuccaHeart.RenderModel();

		//==========================FIN PUCCA=========================



		//==========================LIBRO LUCHA LIBRE ENMASCARADA=========================
		// Pedestal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(177.5f, 0.3f, -17.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		libroMLModelBase = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MuchaLuchaLibroPedestal_M.RenderModel();



		// ========================================
		// Lógica de animación (solo si está activa)
		// ========================================
		if (mainWindow.getcontrollibroML())
		{
			// ----------------------------------------
			// ANIMACIÓN DE IDA (cuando está presionada)
			// ----------------------------------------
			libroML_return = false;

			switch (libroML_stage)
			{
			case 0: // Subida en Y
				if (libroML_posY < libroML_targetY)
					libroML_posY += libroML_speedY * deltaTime;
				else { libroML_posY = libroML_targetY; libroML_stage = 1; }
				break;

			case 1: // Rotación Z
				if (libroML_angleZ > libroML_targetAngleZ)
					libroML_angleZ -= libroML_speedRotZ * deltaTime;
				else { libroML_angleZ = libroML_targetAngleZ; libroML_stage = 2; }
				break;

			case 2: // Movimiento X
				if (libroML_posX > libroML_targetX)
					libroML_posX -= libroML_speedX * deltaTime;
				else { libroML_posX = libroML_targetX; libroML_stage = 3; }
				break;

			case 3: // Descenso global Y
				if (libroML_offsetY > libroML_targetOffsetY)
					libroML_offsetY -= libroML_speedDown * deltaTime;
				else { libroML_offsetY = libroML_targetOffsetY; libroML_stage = 4; }
				break;

			case 4: // Rotación global Y
				if (libroML_angleY < libroML_targetAngleY)
					libroML_angleY += libroML_speedRotY * deltaTime;
				else libroML_angleY = libroML_targetAngleY;
				break;
			}
		}
		else
		{
			// ----------------------------------------
			// ANIMACIÓN DE REGRESO
			// ----------------------------------------
			libroML_return = true;

			switch (libroML_stage)
			{
			case 4: // Subida global Y
				if (libroML_offsetY < 0.0f)
					libroML_offsetY += libroML_speedDown * deltaTime;
				else { libroML_offsetY = 0.0f; libroML_stage = 3; }
				break;

			case 3: // Regreso en X
				if (libroML_posX < 0.0f)
					libroML_posX += libroML_speedX * deltaTime;
				else { libroML_posX = 0.0f; libroML_stage = 2; }
				break;

			case 2: // Rotación Z a 0
				if (libroML_angleZ < 0.0f)


					libroML_angleZ += libroML_speedRotZ * deltaTime;
				else { libroML_angleZ = 0.0f; libroML_stage = 1; }
				break;

			case 1: // Bajar en Y a base
				if (libroML_posY > 4.45f)
					libroML_posY -= libroML_speedY * deltaTime;
				else
				{
					libroML_posY = 4.45f;
					libroML_stage = 0;              //  reinicia a etapa inicial
					libroML_angleY = 0.0f;          //  reestablece rotación global
					libroML_angleZ = 0.0f;          //  corrige orientación local
					libroML_posX = 0.0f;
					libroML_offsetY = 0.0f;
				}
				break;
			}
		}

		// Aplicar transformaciones
		model = libroMLModelBase;
		// Traslación Y
		model = glm::translate(model, glm::vec3(0.0f, libroML_posY, 0.0f));
		// Rotación Z local
		model = glm::rotate(model, glm::radians(libroML_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
		// Traslación global X
		modelaux = glm::translate(glm::mat4(1.0f), glm::vec3(libroML_posX, 0.0f, 0.0f));
		model = modelaux * model;
		// Traslación global Y
		modelaux = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, libroML_offsetY, 0.0f));
		model = modelaux * model;
		// Rotación global Y sobre pivote (mantiene posición)
		libroML_pivot = glm::vec3(169.5f, 0.3f, -17.5f);
		libroML_rotGlobalY =
			glm::rotate(glm::mat4(1.0f), glm::radians(libroML_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), libroML_pivot) *
			libroML_rotGlobalY *
			glm::translate(glm::mat4(1.0f), -libroML_pivot) *
			model;

		// Render final
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MuchaLuchaLibro_M.RenderModel();

		//==========================FIN LIBRO LUCHA LIBRE ENMASCARADA============================
		//==========================CUADRO DEL FUNDADOR =========================================
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(220.0f, 8.2f, -17.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ElFundadorCuadro_M.RenderModel();

		//==========================Terciopelo ==================================================
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(210.0f, 5.0f, -17.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Terciopelo_M.RenderModel();


		// ================================== PIRÁMIDE DEL SOL ==================================

		model = glm::mat4(1.0);
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(15.0f, -1.0f, 240.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		PiramideSol_M.RenderModel();



		


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
