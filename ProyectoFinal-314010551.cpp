/*
PROYECTO FINAL
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <cstdlib>
#include <ctime>

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

// ===================================== DECLARACION DE CAMARAS ==============================

// *************************************** CAMARA 1 ****************************************
Camera camera1;


// ANIMACIÓN DE CAMINATA FRIJOLITO

float frijolitoWalkTime = 0.0f;
float frijolitoWalkSpeed = 0.25f;      // velocidad de oscilación
float frijolitoArmAmplitude = 35.0f;  // grados de movimiento de brazos
float frijolitoLegAmplitude = 30.0f;  // grados de movimiento de piernas

float frijolitoRightArmAngle = 0.0f;
float frijolitoLeftArmAngle = 0.0f;
float frijolitoRightLegAngle = 0.0f;
float frijolitoLeftLegAngle = 0.0f;

bool frijolitoIsWalking = false;
int moveDir;


// Variables compartidas entre cámara y render, POSICIONES INICIALES

static float frijolitoPosX = 100.0f;
static float frijolitoPosZ = 100.0f;
float frijolitoPosY = 0.865f;
float avatarYaw = 0.0f;

// *************************************** CAMARA 2 ****************************************
Camera camera2;
// *************************************** CAMARA 3 ****************************************
Camera camera3;

// ===================================== FIN DECLARACION DE CAMARAS ==============================

//========================Declaración de Texturas ==================================

Texture pisoTexture;
Texture pisoentradaTexture;
Texture plainTexture;
Texture luchadorTexture;
Texture LetreroMLTexture;
Texture MuroLadrilloEntradaTexture;

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

//Modelos Puerta


Model PilaresEntrada_M;
Model PuertaLetreroEntrada_M;
Model PuertaIzqEntrada_M;
Model PuertaDerEntrada_M;



//********************************** CECILIA ******************************************************

Model ajolote;
Model Arbol2;
Model Arbol3;
Model Arbol5;
Model Arbol6;
Model arbol4;
Model arbolB;
Model arbolE;
Model arbolFrondoso;
Model arbolP2;
Model arbolT;
Model arbusto;
Model Arbusto2;
Model arbustoC;
Model arbustoCartoon;
Model arco;
Model Bamboo;
Model bancaring;
Model bambooSilla;
Model Basura;
Model Basura2;
Model casaAzul;
Model casaRoja2;
Model Casita1;
Model CasitaArbol;
Model CasitaArbol12;
Model cherry;
Model frijolito;
Model Garu;
Model hotdog;
Model isla;
Model Lampara;
Model Lamp_M;
Model pasto;
Model pedestal;
Model piedra;
Model piedras;
Model Puesto;
Model Puesto2;
Model puerta;
Model puertaD;
Model quetzalcoatl;
Model reflector;
Model reja;
Model ring;
Model tori;
Model toriP;
Model troncoCorto;


//************************************* AXEL ******************************************************


Model Auto_Cofre;
Model Rico_M;
Model JessieLamp_M;
Model JessieLamp2_M;
Model Entrada_M;
Model Estante_M;
//Brawl Objects
Model Piper_M;
Model Spike_M;
Model Cordelius_M;
Model Frank_M;
Model Gus_M;
Model Stu_M;
Model Sam_M;
Model Colette_M;
Model Surge_M;
Model Brock_M;
Model Doug_M;
Model SamYeti_M;
Model SpikeFire_M;
Model SpikeSakura_M;
Model Dynamike_M;
Model Gale_M;
Model DougDraco_M;
Model Meg_M;
Model Jessie_M;

//Luchadores
Model Luchador_M;
Model Luchador2_M;
Model Luchador3_M;
//Modelos animación luchador
Model Luchador3_M1;
Model Luchador3_M2;
Model Luchador3_M3;
Model Luchador3_M4;
Model Luchador3_M5;
Model Luchador3_M6;
Model Luchador3_M7;
Model Luchador3_M8;
Model Luchador3_M9;

Model Pedestal_M;
Model Carrito_M;
Model Mask_M;
Model Mask2_M;
Model Mask3_M;
Model Mask4_M;
Model Mask5_M;
Model Bulls_M;
Model Ochobit_M;

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

//**************************************PUERTA ******************************************************
//// Textura Animada Letrero

float toffsetletrerou = 0.0f;
float toffsetletrerov = 0.0f;

// Animación puertaizquierda

float angulopuerta;
bool abriendopuertaizq;
float timerPuertaIzq;


// Animación puertaderecha

float muevepuertaderechaZ;
float muevepuertaderechaX;
bool abriendopuertader;
float timerPuertaDer;


bool cicloPuertasTerminado = true;
bool ultimaAnimacionEstado = false;

//************************************** FIN PUERTA ******************************************************

//Animacion ajolote
float ajoloteAvance = 0.0f;     // movimiento base (como el dragonavance)
float anguloAjolote = 0.0f;     // ángulo que usaremos para el seno
float velocidadAjolote = 5.0f;

//=============Animación Pucca===========================

// ---- Movimiento Pucca ----
float puccaPosX = 15.0f;
float puccaPosY = 1.8f;
float puccaPosZ = 90.0f; //IMPORTANTE: SEPARACIÓN PUCCA DE GARU
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

// ==================== Animación Luchador AXEL =============================
//Luchador Axel
static float elapsedTime = 0.0f;
static int currentFrame = 0;
const int totalFrames = 9;       // cantidad de modelos (1 al 40)
const float frameDuration = 10.0f; // segundos entre cada cambio (~12.5 FPS) 0.08f
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
	unsigned int letreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letreroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(letreroVertices, letreroIndices, 32, 6);
	meshList.push_back(obj5);

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
		0.5f,  0.5f,  0.5f,		1.0f,	1.0f,		0.0f,	0.0f,	-1.0f,	//2
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


void CrearMuros()
{
	unsigned int muroEntradaIzq_indices[] = {
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

	GLfloat muroEntradaIzq_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.25f,	0.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.25f,	3.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	3.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	24.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	24.0f,	3.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	3.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.25f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.25f,	3.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	3.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	24.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	24.0f,	3.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	3.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	10.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	10.0f,	1.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.005f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.005f,	3.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	3.0f,		0.0f,	-1.0f,	0.0f,

	};
	Mesh* muroEntradaIzq = new Mesh();
	muroEntradaIzq->CreateMesh(muroEntradaIzq_vertices, muroEntradaIzq_indices, 192, 36);
	meshList.push_back(muroEntradaIzq);

	unsigned int muroEntradaDer_indices[] = {
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

	GLfloat muroEntradaDer_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.25f,	0.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.25f,	3.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	3.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	9.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	9.0f,	3.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	3.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.25f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.25f,	3.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,	3.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	9.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	9.0f,	3.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	3.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	1.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.0f,	1.0f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.005f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.005f,	3.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	3.0f,		0.0f,	-1.0f,	0.0f,

	};
	Mesh* muroEntradaDer = new Mesh();
	muroEntradaDer->CreateMesh(muroEntradaDer_vertices, muroEntradaDer_indices, 192, 36);
	meshList.push_back(muroEntradaDer);
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
	CrearMuros();
	CreateShaders();

	camera1 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -15.0f, 1.0f, 0.5f);
	camera2 = Camera(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f, 1.0f, 0.5f);
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);

	// ================================ TEXTURAS ==========================================

	pisoTexture = Texture("Textures/pisopf.png");
	pisoTexture.LoadTextureA();
	pisoentradaTexture = Texture("Textures/pisoentrada.png");
	pisoentradaTexture.LoadTexture();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	luchadorTexture = Texture("Textures/fam1.jpg");
	luchadorTexture.LoadTextureA();
	LetreroMLTexture = Texture("Textures/LetreroML.tga");
	LetreroMLTexture.LoadTextureA();

	MuroLadrilloEntradaTexture = Texture("Textures/muroladrilloentrada.png");
	MuroLadrilloEntradaTexture.LoadTexture();


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

	PilaresEntrada_M = Model();
	PilaresEntrada_M.LoadModel("Models/pilarespuertaentrada.obj");
	PuertaLetreroEntrada_M = Model();
	PuertaLetreroEntrada_M.LoadModel("Models/puertaentradaletrero.obj");
	PuertaDerEntrada_M = Model();
	PuertaDerEntrada_M.LoadModel("Models/puertaentradaderecha.obj");
	PuertaIzqEntrada_M = Model();
	PuertaIzqEntrada_M.LoadModel("Models/puertaentradaizquierda.obj");


	// ******************************** CECILIA ********************************************

	//ajolote = Model();
	//ajolote.LoadModel("Models/ajolote.obj");

	//Arbol2 = Model();
	//Arbol2.LoadModel("Models/Arbol2.obj");

	//Arbol3 = Model();
	//Arbol3.LoadModel("Models/Arbol3.obj");

	//Arbol5 = Model();
	//Arbol5.LoadModel("Models/Arbol5.obj");

	//Arbol6 = Model();
	//Arbol6.LoadModel("Models/Arbol6.obj");

	//arbol4 = Model();
	//arbol4.LoadModel("Models/arbol4.obj");

	//arbolB = Model();
	//arbolB.LoadModel("Models/arbolB.obj");

	//arbolE = Model();
	//arbolE.LoadModel("Models/arbolE.obj");

	//arbolFrondoso = Model();
	//arbolFrondoso.LoadModel("Models/arbolFrondoso.obj");

	//arbolP2 = Model();
	//arbolP2.LoadModel("Models/ArbolP2.obj");

	//arbolT = Model();
	//arbolT.LoadModel("Models/arbolT.obj");

	//arbusto = Model();
	//arbusto.LoadModel("Models/arbusto.obj");

	//Arbusto2 = Model();
	//Arbusto2.LoadModel("Models/Arbusto2.obj");

	//arbustoC = Model();
	//arbustoC.LoadModel("Models/arbustoC.obj");

	//arbustoCartoon = Model();
	//arbustoCartoon.LoadModel("Models/arbustoCartoon.obj");

	//arco = Model();
	//arco.LoadModel("Models/arco.obj");

	//Bamboo = Model();
	//Bamboo.LoadModel("Models/Bamboo.obj");

	//bambooSilla = Model();
	//bambooSilla.LoadModel("Models/bambooSilla.obj");

	bancaring = Model();
	bancaring.LoadModel("Models/bancaring.obj");

	//Basura = Model();
	//Basura.LoadModel("Models/Basura.obj");

	//Basura2 = Model();
	//Basura2.LoadModel("Models/Basura2.obj");

	//casaAzul = Model();
	//casaAzul.LoadModel("Models/casaAzul.obj");

	//casaRoja2 = Model();
	//casaRoja2.LoadModel("Models/casaRoja2.obj");

	//Casita1 = Model();
	//Casita1.LoadModel("Models/Casita1.obj");

	//CasitaArbol = Model();
	//CasitaArbol.LoadModel("Models/CasitaArbol.obj");

	//CasitaArbol12 = Model();
	//CasitaArbol12.LoadModel("Models/CasitaArbol12.obj");

	//cherry = Model();
	//cherry.LoadModel("Models/cherry.obj");

	//frijolito = Model();
	//frijolito.LoadModel("Models/frijolito.obj");

	//Garu = Model();
	//Garu.LoadModel("Models/Garu.obj");

	hotdog = Model();
	hotdog.LoadModel("Models/hotdog.obj");

	//isla = Model();
	//isla.LoadModel("Models/isla.obj");

	//Lampara = Model();
	//Lampara.LoadModel("Models/LamparaC.obj");

	//Lamp_M = Model();
	//Lamp_M.LoadModel("Models/lampara.obj");

	//pasto = Model();
	//pasto.LoadModel("Models/pasto.obj");

	//pedestal = Model();
	//pedestal.LoadModel("Models/pedestal.obj");

	//piedra = Model();
	//piedra.LoadModel("Models/piedras.obj");

	//piedras = Model();
	//piedras.LoadModel("Models/piedras.obj");

	//Puesto = Model();
	//Puesto.LoadModel("Models/Puesto.obj");

	//Puesto2 = Model();
	//Puesto2.LoadModel("Models/Puesto2.obj");

	//puerta = Model();
	//puerta.LoadModel("Models/puertaM.obj");

	//puertaD = Model();
	//puertaD.LoadModel("Models/puertaD.obj");

	//quetzalcoatl = Model();
	//quetzalcoatl.LoadModel("Models/quetzalcoatl.obj");

	//reflector = Model();
	//reflector.LoadModel("Models/reflector.obj");

	//reja = Model();
	//reja.LoadModel("Models/reja.obj");

	ring = Model();
	ring.LoadModel("Models/ring.obj");

	//tori = Model();
	//tori.LoadModel("Models/tori.obj");

	//toriP = Model();
	//toriP.LoadModel("Models/tori2.obj");

	//troncoCorto = Model();
	//troncoCorto.LoadModel("Models/troncoCorto.obj");


	//********************************** AXEL ********************************************************
	//Lamp_M = Model();
	//Lamp_M.LoadModel("Models/lampara.obj");

	//Rico_M = Model();
	//Rico_M.LoadModel("Models/ricolamp.obj");
	//JessieLamp_M = Model();
	//JessieLamp_M.LoadModel("Models/jessielamp.obj");
	//JessieLamp2_M = Model();
	//JessieLamp2_M.LoadModel("Models/jessielamp2.obj");

	//Entrada_M = Model();
	//Entrada_M.LoadModel("Models/entrada.obj");
	//Estante_M = Model();
	//Estante_M.LoadModel("Models/estante.obj");
	////Personajes Brawl Stars
	//Piper_M = Model();
	//Piper_M.LoadModel("Models/piper.obj");
	//Spike_M = Model();
	//Spike_M.LoadModel("Models/spike.obj");
	//Cordelius_M = Model();
	//Cordelius_M.LoadModel("Models/cordelius.obj");
	//Frank_M = Model();
	//Frank_M.LoadModel("Models/frank.obj");
	//Gus_M = Model();
	//Gus_M.LoadModel("Models/gus.obj");
	//Stu_M = Model();
	//Stu_M.LoadModel("Models/stu.obj");
	//Sam_M = Model();
	//Sam_M.LoadModel("Models/sam.obj");
	//Colette_M = Model();
	//Colette_M.LoadModel("Models/colette.obj");
	//Surge_M = Model();
	//Surge_M.LoadModel("Models/surge.obj");
	//Brock_M = Model();
	//Brock_M.LoadModel("Models/brock.obj");
	//Doug_M = Model();
	//Doug_M.LoadModel("Models/doug.obj");
	//SamYeti_M = Model();
	//SamYeti_M.LoadModel("Models/samyeti.obj");
	//SpikeFire_M = Model();
	//SpikeFire_M.LoadModel("Models/spikefire.obj");
	//SpikeSakura_M = Model();
	//SpikeSakura_M.LoadModel("Models/spikesakura.obj");
	//Dynamike_M = Model();
	//Dynamike_M.LoadModel("Models/dynamike.obj");
	//Gale_M = Model();
	//Gale_M.LoadModel("Models/gale.obj");
	//DougDraco_M = Model();
	//DougDraco_M.LoadModel("Models/dougdraco.obj");
	//Meg_M = Model();
	//Meg_M.LoadModel("Models/meg.obj");
	//Jessie_M = Model();
	//Jessie_M.LoadModel("Models/jessie.obj");



	////Luchadores
	//Luchador_M = Model();
	//Luchador_M.LoadModel("Models/luchador.obj");
	//Luchador2_M = Model();
	//Luchador2_M.LoadModel("Models/resrler.obj");
	//Luchador3_M = Model();
	//Luchador3_M.LoadModel("Models/luchador3.obj");


	////Modelos animación luchador
	//Luchador3_M1 = Model();
	//Luchador3_M1.LoadModel("Models/luchadorAnim80.obj");
	//Luchador3_M2 = Model();
	//Luchador3_M2.LoadModel("Models/luchadorAnim81.obj");
	//Luchador3_M3 = Model();
	//Luchador3_M3.LoadModel("Models/luchadorAnim82.obj");
	//Luchador3_M4 = Model();
	//Luchador3_M4.LoadModel("Models/luchadorAnim83.obj");
	//Luchador3_M5 = Model();
	//Luchador3_M5.LoadModel("Models/luchadorAnim84.obj");
	//Luchador3_M6 = Model();
	//Luchador3_M6.LoadModel("Models/luchadorAnim85.obj");
	//Luchador3_M7 = Model();
	//Luchador3_M7.LoadModel("Models/luchadorAnim86.obj");
	//Luchador3_M8 = Model();
	//Luchador3_M8.LoadModel("Models/luchadorAnim87.obj");
	//Luchador3_M9 = Model();
	//Luchador3_M9.LoadModel("Models/luchadorAnim88.obj");


	//Pedestal_M = Model();
	//Pedestal_M.LoadModel("Models/pedestal.obj");
	//Carrito_M = Model();
	//Carrito_M.LoadModel("Models/shop.obj");
	//Mask_M = Model();
	//Mask_M.LoadModel("Models/mask.obj");
	//Mask2_M = Model();
	//Mask2_M.LoadModel("Models/mask2.obj");
	//Mask3_M = Model();
	//Mask3_M.LoadModel("Models/mask3.obj");
	//Mask4_M = Model();
	//Mask4_M.LoadModel("Models/mask4.obj");
	//Mask5_M = Model();
	//Mask5_M.LoadModel("Models/mask5.obj");
	//Bulls_M = Model();
	//Bulls_M.LoadModel("Models/bulls.obj");
	//Ochobit_M = Model();
	//Ochobit_M.LoadModel("Models/8bit.obj");

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
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader


	//=========================================== DECLARACION MATRICES ================================================

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelauxletrero(1.0);

	//FRIJOLITO
	glm::vec3 frijolitoPos;
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
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



	//Inicializar variables de letrero
	toffsetletrerou = 0.0f;
	toffsetletrerov = 0.0f;

	//Inicializar variables puerta izquierda

	angulopuerta = 0.0f;
	abriendopuertaizq = true;
	timerPuertaIzq = 0.0f;


	//Inicializar variables puerta derecha

	muevepuertaderechaZ = 0.0f;
	muevepuertaderechaX = 0.0f;
	abriendopuertader = true;
	timerPuertaDer = 0.0f;

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();




		// ======================================================
		// CONTROL DE CÁMARAS
		// ======================================================
		if (mainWindow.getcontrolcamara() == 2)
		{
			// Cámara 1 - Tercera persona
			camera1.mouseControlAvatar(mainWindow.getXChange(), mainWindow.getYChange());
			camera1.controlAvatarMovement(mainWindow.getsKeys(), deltaTime, frijolitoPosX, frijolitoPosZ);

			frijolitoPos = glm::vec3(frijolitoPosX, frijolitoPosY, frijolitoPosZ);
			camera1.followTarget(frijolitoPos, 0.0f);

			view = camera1.calculateViewMatrix();
			eyePos = camera1.getCameraPosition();
		}
		else if (mainWindow.getcontrolcamara() == 1)
		{
			camera2.keyControlXZ(mainWindow.getsKeys(), deltaTime);
			view = camera2.calculateViewMatrix();
			eyePos = camera2.getCameraPosition();
		}
		else if (mainWindow.getcontrolcamara() == 0)
		{
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
		uniformTextureOffset = shaderList[0].getOffsetLocation(); // para la textura con movimiento
		
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
		toffset = glm::vec2(0.0f, 0.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f * 0.788f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		// ======================================== PISO ENTRADA ============================================================

		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(256.4f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoentradaTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();





		// ======================================== PUERTA ENTRADA ============================================================
		//PUERTAS
		//================================================================

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);


		model = glm::translate(model, glm::vec3(236.0f, 16.0f, -122.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		modelaux = model;
		color = glm::vec3(0.6627f, 0.6627f, 0.6627f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PilaresEntrada_M.RenderModel();

		// Detectar cambio de mainWindow.getanimapuertas() para reiniciar
		if (!ultimaAnimacionEstado && mainWindow.getanimapuertas())
		{
			// Solo reiniciamos si las puertas están en posición inicial
			if (angulopuerta == 0.0f &&
				muevepuertaderechaX == 0.0f &&
				muevepuertaderechaZ == 0.0f)
			{
				cicloPuertasTerminado = false;    // permite iniciar animación
				abriendopuertaizq = true;         // reiniciamos dirección izquierda
				abriendopuertader = true;         // reiniciamos dirección derecha
			}
		}

		// Guardamos el estado actual para detectar cambios
		ultimaAnimacionEstado = mainWindow.getanimapuertas();

		// Animación de puertas solo si está activada y no ha terminado el ciclo
		if (mainWindow.getanimapuertas() && !cicloPuertasTerminado)
		{
			// ------- PUERTA IZQUIERDA -------
			if (abriendopuertaizq)
			{
				angulopuerta += 0.25f * deltaTime;
				if (angulopuerta >= 90.0f)
				{
					angulopuerta = 90.0f;
					timerPuertaIzq += deltaTime;
					if (timerPuertaIzq >= 120.0f)
					{
						abriendopuertaizq = false;
						timerPuertaIzq = 0.0f;
					}
				}
			}
			else
			{
				angulopuerta -= 0.25f * deltaTime;
				if (angulopuerta <= 0.0f)
				{
					angulopuerta = 0.0f;
					// se queda en cero hasta reinicio
				}
			}

			// ------- PUERTA DERECHA (lógica invertida) -------
			if (abriendopuertader)
			{
				muevepuertaderechaZ += 0.01f * deltaTime;    // antes era -=
				if (muevepuertaderechaZ >= 1.32f)            // antes era <= -1.32f
				{
					muevepuertaderechaZ = 1.32f;
					muevepuertaderechaX -= 0.025f * deltaTime; // antes era +=
					if (muevepuertaderechaX <= -6.4f)           // antes era >= 6.4f
					{
						muevepuertaderechaX = -6.4f;
						timerPuertaDer += deltaTime;
						if (timerPuertaDer >= 120.0f)
						{
							abriendopuertader = false;
							timerPuertaDer = 0.0f;
						}
					}
				}
			}
			else
			{
				muevepuertaderechaX += 0.025f * deltaTime;     // antes era -=
				if (muevepuertaderechaX >= 0.0f)
				{
					muevepuertaderechaX = 0.0f;
					muevepuertaderechaZ -= 0.01f * deltaTime;   // antes era +=
					if (muevepuertaderechaZ <= 0.0f)
						muevepuertaderechaZ = 0.0f; // se queda en cero hasta reinicio
				}
			}


			// ------- Detectar si ciclo completo terminó -------
			if (angulopuerta == 0.0f &&
				muevepuertaderechaX == 0.0f &&
				muevepuertaderechaZ == 0.0f)
			{
				cicloPuertasTerminado = true; // se queda bloqueado hasta próximo cambio de animapuertas
				mainWindow.setanimapuertas(false); // setear la animación en false para que cuando la apretemos vuelva a empezar
			}
		}





		model = modelaux;
		model = glm::translate(model, glm::vec3(4.7455f, 0.0f, 0.0f));
		model = glm::rotate(model, angulopuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		color = glm::vec3(0.4902f, 0.3529f, 0.3098f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaIzqEntrada_M.RenderModel();



		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.7455f + muevepuertaderechaX, 0.0f, muevepuertaderechaZ));
		color = glm::vec3(0.4902f, 0.3529f, 0.3098f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaDerEntrada_M.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 6.84f, 0.0f));
		modelauxletrero = model;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuertaLetreroEntrada_M.RenderModel();

		// =========================   FIN PUERTAS ======================================================================================

		// =========================   MUROS ============================================================================================

		// Muro Izq Entrada
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(236.0f, 11.55f, 101.0f));
		model = glm::scale(model, glm::vec3(4.0f, 25.0f, 398.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		MuroLadrilloEntradaTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		// Muro Der Entrada
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(236.0f, 11.55f, -223.5f));
		model = glm::scale(model, glm::vec3(4.0f, 25.0f, 153.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		MuroLadrilloEntradaTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[7]->RenderMesh();

		// ************************************* AVATAR ***********************************************
		// ********************************************************************************************
		// ********************************************************************************************
		// 
		// Rotación según la cámara
		avatarYaw = camera1.getYaw();

		// Detección de movimiento
		frijolitoIsWalking = camera1.isAvatarMoving();
		moveDir = camera1.getAvatarMoveDirection();

		if (frijolitoIsWalking)
		{
			frijolitoWalkTime += deltaTime * frijolitoWalkSpeed;

			
			// =======================================================
			// ANIMACIÓN SEGÚN DIRECCIÓN
			// =======================================================
			if (moveDir == 1) // Adelante
			{
				frijolitoRightArmAngle = sin(frijolitoWalkTime + 3.14f) * frijolitoArmAmplitude;
				frijolitoLeftArmAngle = sin(frijolitoWalkTime) * frijolitoArmAmplitude;

				frijolitoRightLegAngle = sin(frijolitoWalkTime) * frijolitoLegAmplitude;
				frijolitoLeftLegAngle = sin(frijolitoWalkTime + 3.14f) * frijolitoLegAmplitude;
			}
			else if (moveDir == -1) // Atrás
			{
				frijolitoRightArmAngle = sin(frijolitoWalkTime) * frijolitoArmAmplitude;
				frijolitoLeftArmAngle = sin(frijolitoWalkTime + 3.14f) * frijolitoArmAmplitude;

				frijolitoRightLegAngle = sin(frijolitoWalkTime + 3.14f) * frijolitoLegAmplitude;
				frijolitoLeftLegAngle = sin(frijolitoWalkTime) * frijolitoLegAmplitude;
			}
			else if (moveDir == 2) // Derecha
			{
				frijolitoRightArmAngle = sin(frijolitoWalkTime) * (frijolitoArmAmplitude * 0.5f);
				frijolitoLeftArmAngle = sin(frijolitoWalkTime + 3.14f) * (frijolitoArmAmplitude * 0.5f);

				frijolitoRightLegAngle = sin(frijolitoWalkTime + 3.14f) * (frijolitoLegAmplitude * 0.5f);
				frijolitoLeftLegAngle = sin(frijolitoWalkTime) * (frijolitoLegAmplitude * 0.5f);
			}
			else if (moveDir == -2) // Izquierda
			{
				frijolitoRightArmAngle = sin(frijolitoWalkTime + 3.14f) * (frijolitoArmAmplitude * 0.5f);
				frijolitoLeftArmAngle = sin(frijolitoWalkTime) * (frijolitoArmAmplitude * 0.5f);

				frijolitoRightLegAngle = sin(frijolitoWalkTime) * (frijolitoLegAmplitude * 0.5f);
				frijolitoLeftLegAngle = sin(frijolitoWalkTime + 3.14f) * (frijolitoLegAmplitude * 0.5f);
			}
		}
		else
		{
			// Quieto: brazos y piernas relajados
			frijolitoRightArmAngle = 0.0f;
			frijolitoLeftArmAngle = 0.0f;
			frijolitoRightLegAngle = 0.0f;
			frijolitoLeftLegAngle = 0.0f;
		}




		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(frijolitoPosX, frijolitoPosY, frijolitoPosZ));
		model = glm::rotate(model, glm::radians(avatarYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		modelauxfrijolito = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		FrijolitoHeadBody_M.RenderModel();

		// Brazo derecho
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(frijolitoRightArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoRightHand_M.RenderModel();

		// Brazo izquierdo
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(frijolitoLeftArmAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoLeftHand_M.RenderModel();

		// Pierna derecha
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(frijolitoRightLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoRightLeg_M.RenderModel();

		// Pierna izquierda
		model = modelauxfrijolito;
		model = glm::rotate(model, glm::radians(frijolitoLeftLegAngle), glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoLeftLeg_M.RenderModel();

		// ************************************* FIN AVATAR *******************************************
		// ********************************************************************************************
		// ********************************************************************************************





		// ************************************ DANIEL ******************************************
		// **************************************************************************************
		// **************************************************************************************

		//===================================== Ricochet =======================================

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(135.0f, 8.865f, 160.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Ricochet_M.RenderModel();

		//===================================== Buena Niña =======================================

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(135.0f, 8.865f, 180.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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

		//============================Terciopelo ==================================================
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


		// ************************************ CECILIA *****************************************
		// **************************************************************************************
		// **************************************************************************************

		//// Casa fideos (Casita1)
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-170.0f, -0.1f, -15.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(11.5f, 11.5f, 11.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Casita1.RenderModel();

		//// Casa árbol roja
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-135.0f, 9.85f, -55.0f));
		//model = glm::rotate(model, 180.5f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(13.15f, 13.15f, 13.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//CasitaArbol.RenderModel();

		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-225.0f, -0.5f, -63.0f));
		//model = glm::rotate(model, 180.5f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(9.15f, 9.15f, 9.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolFrondoso.RenderModel();

		//// Casa roja
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-75.0f, -2.7f, -40.0f));
		//model = glm::rotate(model, 360.7f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//casaRoja2.RenderModel();


		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-55.0f, -1.5f, -40.0f));
		//model = glm::rotate(model, 360.7f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(7.25f, 11.25f, 7.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolP2.RenderModel();

		//// Arbusto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-65.0f, -0.7f, -70.0f));
		//model = glm::rotate(model, 360.7f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(7.25f, 7.25f, 7.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbusto.RenderModel();

		//// tronco cortado
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-75.0f, 0.3f, -60.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(7.25f, 7.25f, 7.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//troncoCorto.RenderModel();
		//// tronco cortado
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-55.0f, -0.25f, -60.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//troncoCorto.RenderModel();

		//// Casita techo negro arboles
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-125.0f, 3.0f, 10.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(14.2f, 14.2f, 14.2f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//CasitaArbol12.RenderModel();

		//// Casita Azul
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-85.0f, -1.1f, 7.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//casaAzul.RenderModel();

		//// Cherry
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-55.0f, -0.5f, 7.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.85f, 3.85f, 3.85f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//cherry.RenderModel();



		//// tori
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-50.0f, -1.0f, -17.0f));
		//model = glm::rotate(model, 270.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.15f, 4.15f, 5.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//toriP.RenderModel();


		//// Puesto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-90.0f, -0.75f, 90.0f));
		//model = glm::rotate(model, 270.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.15f, 3.15f, 3.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Puesto.RenderModel();

		//// Puesto2
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-58.0f, -4.1f, -150.0f));
		//model = glm::rotate(model, -178.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.15f, 3.15f, 3.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Puesto2.RenderModel();

		//// Puesto2
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-58.0f, -4.1f, -120.0f));
		//model = glm::rotate(model, -178.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.15f, 3.15f, 3.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoC.RenderModel();

		//// Garu
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-95.0f, -1.7f, -125.0f));
		//model = glm::rotate(model, 268.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(11.15f, 11.15f, 11.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Garu.RenderModel();

		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-100.0f, -1.0f, -160.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 11.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-100.0f, -1.0f, -170.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 10.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-100.0f, -1.0f, -165.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 10.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();

		////Bamboo fideos
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-197.0f, -1.0f, 45.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-187.0f, -1.0f, 30.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-197.0f, -1.0f, 42.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-197.0f, -1.0f, 48.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 8.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-197.0f, -1.0f, 55.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-186.0f, -1.0f, 60.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-180.0f, -1.0f, 31.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 8.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-175.0f, -1.0f, 38.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-187.0f, -1.0f, 65.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-187.0f, -1.0f, 40.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-179.0f, -1.0f, 45.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-185.0f, -1.0f, 42.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 8.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-170.0f, -1.0f, 65.5f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-173.0f, -1.0f, 50.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-161.0f, -1.0f, 35.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-179.0f, -1.0f, 55.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 8.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-170.0f, -1.0f, 36.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-160.0f, -1.0f, 55.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 8.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-165.0f, -1.0f, 30.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-170.0f, -1.0f, 37.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 9.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();

		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-192.0f, -1.0f, 55.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-177.0f, -1.0f, 65.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();
		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-170.0f, -1.0f, 30.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.15f, 6.15f, 6.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Bamboo.RenderModel();

		//// Bamboo
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(105.0f, -1.5f, 39.0f));
		//model = glm::rotate(model, -8.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.15f, 3.15f, 3.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//bambooSilla.RenderModel();




		// Ring
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -0.9f, 169.0f));
		model = glm::rotate(model, 91.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.29f, 0.19f, 0.29f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		ring.RenderModel();


		// Ring Banca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -0.7f, 85.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.20f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bancaring.RenderModel();

		// Ring Banca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -0.7f, 105.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.20f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bancaring.RenderModel();

		// Ring Banca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -0.7f, 65.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.20f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bancaring.RenderModel();


		// Ring Banca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -1.5f, 240.0f));
		model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.20f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bancaring.RenderModel();

		// Ring Banca
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(165.0f, -1.5f, 260.0f));
		model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.20f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bancaring.RenderModel();

		//// Basura
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-71.0f, -0.7f, 7.0f));
		//model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Basura.RenderModel();
		//// Basura
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-71.0f, -0.8f, 9.0f));
		//model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Basura.RenderModel();

		//// Basura
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(75.0f, -2.29f, -160.0f));  // misma Z que tori
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 10.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Basura2.RenderModel();

		//// Arbol
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(75.0f, 0.0f, -100.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 10.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolT.RenderModel();
		//glDisable(GL_BLEND);



		//// Arbusto
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(155.0f, -1.1f, -165.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbol2.RenderModel();
		//glDisable(GL_BLEND);

		//// piedras
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(155.0f, -0.2f, -195.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//piedras.RenderModel();
		//glDisable(GL_BLEND);

		//// Arbol
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(105.0f, 0.0f, -150.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.15f, 10.15f, 10.15f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolT.RenderModel();
		//glDisable(GL_BLEND);

		//// Arbol
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(185.0f, 0.0f, -195.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolE.RenderModel();
		//glDisable(GL_BLEND);

		//// Arbol
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(195.0f, -1.1f, -75.0f));
		//model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbolB.RenderModel();
		//glDisable(GL_BLEND);

		//// Arbusto

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(28.0f, -1.1f, -98.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(8.0f, 4.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();


		//// Quetzalcoatl
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-5.0f, -1.5f, 250.0f));
		//model = glm::rotate(model, -270.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//quetzalcoatl.RenderModel();



		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-120.0f, -3.0f, 270.0f));
		//model = glm::rotate(model, 360.7f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(40.25f, 40.25f, 40.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		////color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbol3.RenderModel();

		//// Piedras
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-108.0f, -0.8f, 210.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(2.0f, 1.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//piedra.RenderModel();

		//// Arbusto

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-128.0f, -1.1f, 250.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 2.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-90.0f, -1.1f, 270.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 2.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-110.0f, -1.1f, 260.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 2.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-180.0f, -1.1f, 280.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 2.5f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();

		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-130.0f, -1.1f, 220.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 2.5f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbustoCartoon.RenderModel();



		//// Arbusto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-70.0f, 5.5f, 220.0f));
		//model = glm::scale(model, glm::vec3(10.25f, 10.25f, 10.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbusto2.RenderModel();
		//// Arbusto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-90.0f, 2.0f, 250.0f));
		//model = glm::scale(model, glm::vec3(7.25f, 5.25f, 5.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbusto2.RenderModel();

		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-100.0f, -1.5f, 200.0f));
		//model = glm::scale(model, glm::vec3(3.25f, 3.25f, 3.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//arbol4.RenderModel();

		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-130.0f, 26.0f, 80.0f));
		//model = glm::scale(model, glm::vec3(45.25f, 35.25f, 30.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbol5.RenderModel();

		//// Arbol
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(130.0f, -0.4f, 30.0f));
		//model = glm::scale(model, glm::vec3(45.25f, 35.25f, 30.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Arbol6.RenderModel();

		//// Pasto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(100.0f, -1.0f, 30.0f));
		//model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pasto.RenderModel();
		//// Pasto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(100.0f, -1.0f, 20.0f));
		//model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pasto.RenderModel();
		//// Pasto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(90.0f, -1.0f, 15.0f));
		//model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pasto.RenderModel();
		//// Pasto
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(130.0f, -1.0f, 30.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pasto.RenderModel();
		//
		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-145.0f, -1.2f, -35.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lampara.RenderModel();

		//// Basura
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-49.0f, -0.8f, -70.0f));
		//model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Basura.RenderModel();

		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-47.0f, 0.0f, -75.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();

		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-47.0f, 0.0f, 35.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();

		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(26.0f, 0.0f, -45.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();


		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(26.0f, 0.0f, 65.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();

		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -129.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();

		//// Lampara
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -111.0f));
		//model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();


		//HotDog
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(215.0f, 0.5f, 240.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hotdog.RenderModel();


		//// Movimiento del ajolote (sube y baja)
		//// Actualizamos el ángulo del ajolote igual que el dragón
		//anguloAjolote += velocidadAjolote * deltaTime;

		//// Movimiento vertical tipo “flotante”
		//float movimientoVertical = 0.3f * sin(glm::radians(anguloAjolote));


		////Pedestal Ajolote
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-180.0f, -1.5f, -120.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glm::mat4 modelAux = model;

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pedestal.RenderModel();


		//// AJOLOTE 
		//model = modelAux;

		//// aplicamos la lógica del dragón pero en Y
		//model = glm::translate(model, glm::vec3(0.0f, 5.0f + movimientoVertical, 0.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//ajolote.RenderModel();



		//// Pedestal luchador2
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(155.0f, -1.5f, -120.0f));
		//model = glm::rotate(model, 360.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//pedestal.RenderModel();

		////*************************************** AXEL ************************************
		////*********************************************************************************
		////*********************************************************************************

		////Antorchas
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(119.1456f, -0.7f, -70.6f));
		//pointLights[4].SetPos(glm::vec3(model[3].x, model[3].y + 14.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();
		////Antocha 2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(62.4096f, -0.7f, 25.2f));
		//pointLights[4].SetPos(glm::vec3(model[3].x, model[3].y + 14.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();
		////Antocha 3
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(62.4096f, -0.7f, 252.0f));
		//pointLights[4].SetPos(glm::vec3(model[3].x, model[3].y + 14.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();
		////Antocha 4
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-91.2504f, -0.7f, 252.0f));
		//pointLights[4].SetPos(glm::vec3(model[3].x, model[3].y + 14.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Lamp_M.RenderModel();

		////Rico Lamp
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(73.0f, -1.0f, -245.0));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//pointLights[3].SetPos(glm::vec3(model[3].x + 5.0f, model[3].y + 30.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Rico_M.RenderModel();

		////Jessie Lamp
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(213.0f, -1.0f, -242.0));
		//model = glm::rotate(model, 70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////pointLights[3].SetPos(glm::vec3(model[3].x + 5.0f, model[3].y + 30.0f, model[3].z));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//modelaux = model;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//JessieLamp_M.RenderModel();
		//model = glm::translate(model, glm::vec3(-1.1f, 4.6908f, -0.040381f));
		//model = modelaux;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//JessieLamp2_M.RenderModel();

		////Estante
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(130.0f, -13.0f, -300.0));
		//model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//modelaux = model;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Estante_M.RenderModel();
		////Estante2
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.7));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Estante_M.RenderModel();
		////Objetos estante1
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(73.0f, 22.6f, -280.0));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//modelaux = model;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Rico_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Piper_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-16.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Spike_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Cordelius_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-48.0f, 0.0f, 0.0));
		//model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Frank_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-64.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Gus_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-16.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Stu_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-32.0f, -19.4f, 0.0));
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Sam_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-48.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Colette_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-64.0f, -19.4f, 0.0));
		//model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Surge_M.RenderModel();
		////Objetos estante2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(158.0f, 22.6f, -280.0));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//modelaux = model;
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Brock_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(0.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Doug_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-16.0f, 0.0f, 0.0));
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//SamYeti_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//SpikeFire_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-48.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//SpikeSakura_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-64.0f, 0.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Dynamike_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-16.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Gale_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-32.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//DougDraco_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-48.0f, -19.4f, 0.0));
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Meg_M.RenderModel();
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-64.0f, -19.4f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Jessie_M.RenderModel();

		////Pedestal
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-173.0f, -1.5f, -275.0));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Pedestal_M.RenderModel();
		//model = modelaux;
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::translate(model, glm::vec3(0.0f, 192.0f, -25.0));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Luchador_M.RenderModel();
		////Pedestal2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-143.0f, -1.5f, -275.0));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Pedestal_M.RenderModel();
		//model = modelaux;
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		//model = glm::translate(model, glm::vec3(0.0f, 192.0f, 0.0));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Luchador2_M.RenderModel();
		////Pedestal3
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-113.0f, -1.5f, -275.0));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(4.25f, 4.25f, 4.25f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Pedestal_M.RenderModel();
		//model = modelaux;
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 19.35f, 0.0));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Luchador3_M.RenderModel();

		////Animación Luchador
		//// Actualizar tiempo
		//elapsedTime += deltaTime; // Asegúrate de tener tu deltaTime calculado
		//if (elapsedTime >= frameDuration) {
		//	elapsedTime = 0.0f;
		//	currentFrame++;
		//	if (currentFrame >= totalFrames)
		//		currentFrame = 0;
		//}
		//// Matriz de transformación
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-203.0f, 0.0f, -250.0));
		//model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//// Dibujar el modelo actual (según frame)
		//switch (currentFrame) {
		//case 0:  Luchador3_M1.RenderModel(); break;
		//case 1:  Luchador3_M2.RenderModel(); break;
		//case 2:  Luchador3_M3.RenderModel(); break;
		//case 3:  Luchador3_M4.RenderModel(); break;
		//case 4:  Luchador3_M5.RenderModel(); break;
		//case 5:  Luchador3_M6.RenderModel(); break;
		//case 6:  Luchador3_M7.RenderModel(); break;
		//case 7:  Luchador3_M8.RenderModel(); break;
		//case 8:  Luchador3_M9.RenderModel(); break;
		//}

		////Letrero luchador
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-143.0f, -0.95f, -235.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(15.0f, 15.0f, 30.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//luchadorTexture.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[4]->RenderMesh();

		////Tienda mask
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(62.4096f, -1.0f, -123.0f));
		//model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Carrito_M.RenderModel();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(66.192f, 21.1f, -118.8f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mask_M.RenderModel();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(61.464f, 20.5f, -118.8f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mask2_M.RenderModel();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(64.7736f, 20.5f, -124.8f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mask3_M.RenderModel();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(68.0832f, 20.5f, -131.4f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mask4_M.RenderModel();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(69.5016f, 21.1f, -126.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Mask5_M.RenderModel();

		////Bulls
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(47.3008f, -2.0f, 20.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Bulls_M.RenderModel();
		//glDisable(GL_BLEND);
		////NPC2
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(60.9912f, -1.0f, 96.4));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Ochobit_M.RenderModel();




		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		toffsetletrerou += 0.003;

		if (toffsetletrerou > 1.0)
		toffsetletrerou = 0.0;

		toffset = glm::vec2(toffsetletrerou, toffsetletrerov);

		model = modelauxletrero;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.17f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(13.5f, 1.0f, 3.25f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LetreroMLTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();


		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
