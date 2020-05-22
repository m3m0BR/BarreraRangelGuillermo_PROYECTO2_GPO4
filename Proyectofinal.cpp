/*---------------------------------------------------------*/
/* ----------------   Proyecto Final --------------------------*/
/*-----------------    2020-2   ---------------------------*/
/*------------- Alumnos: Barrera Rangel Guillermo  ---------------*/

//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include "camera.h"
#include "Model.h"
#include "Texture.h"


// Other Libs
#include "SOIL2/SOIL2.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint skyboxVBO, skyboxVAO;

//audio
using namespace std;

//Camera
Camera camera(glm::vec3(0.0f, 10.0f, 0.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 30.0f, 50.0f);
glm::vec3 lightDirection(-1.0f, -1.0f, -30.0f);

void myData(void);
void myData2(void);
void display(Shader, Shader, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = 0.0f,
moDx = 0.0f,
moDz = 0.0f,
rotD = 0.0f,
	rotX = 0.0f;
float movAuto_z = 0.0f,
movAuto_x = 0.0f,
MovLLanta = 0.0f, giro = 0.0f,
MovJeepx = 0.0f,
movavion_x = 0.0f,
movavion_y = 0.0f,
movavion_z = 0.0f,
orienta = 0.0f;



bool animacion = false, recorrido1 = true, recorrido2 = false, recorrido3 = true, recorrido4 = true,
recorrido5 = false, recorrido6 = false, recorrido7 = false, recorrido8 = false, recorrido9 = false,
jeep1 = true, jeep2, play2 = false, play3 = false, play = true, adelante = false, stop = false, m = false,

recorrido_1 = true,
recorrido_2 = false,
recorrido_3 = false,
recorrido_4 = false,
recorrido_5 = false,
recorrido_6 = false,
recorrido_7 = false,
recorrido_8 = false;



//Texture
unsigned int	t_smile,
				t_piso;

//Keyframes
//Variables de dibujo y modificacion por el usuario
float	
posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotx = 0.0f,
salto1 = 0.0f,
salto2 = 0.0f;


unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{
	t_piso = generateTextures("Texturas/piso.jpg", 0);
	
}

void myData()
{	
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void myData2()
{
	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	// SkyBox
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

}
float var = 0.0f, valor=rotD;

void animate(void)
{
	if (m) {
		PlaySound(TEXT("audio/halo1.wav"), NULL, SND_SYNC);
		m = false;
	}

	//  ANIMACION JEEP
	if (jeep1) {
		if (MovJeepx > -200) {
			MovJeepx -= 2.0f;
		}
		else{
			jeep1 = false;
			jeep2 = true;
		}
	}
	else if (jeep2) {
		MovJeepx = 200;
		jeep1 = true;
		jeep2 = false;
	}

	//ANIMACIÓN LAMBORGINI
	if (recorrido1) {
		if (movAuto_z < 155) {
			movAuto_z += 2.0f;
			printf("Posicion %f \n", movAuto_z);
			MovLLanta += 30.0f;
			printf("Posicion %f \n", MovLLanta);

		}
		else {
			recorrido1 = false;
			recorrido2 = true;

		}
	}
	else if (recorrido2) {
		if (giro > -90) {
			giro -= 10.0f;
			printf("Posicion %f \n", giro);
			if (movAuto_z < 163) {
				movAuto_z += 1.0f;
				printf("Posicion %f \n", movAuto_z);
			}
		}
		else {
			recorrido2 = false;
			recorrido3 = true;
		}
	}
	else if (recorrido3) {
		if (movAuto_x > -145) {
			movAuto_x -= 2.0f;
			printf("Posicion %f \n", movAuto_x);
			MovLLanta += 30.0f;
			printf("Posicion %f \n", MovLLanta);
		}
		else {
			recorrido3 = false;
			recorrido4 = true;

		}

	}
	else if (recorrido4) {
		if (giro > -180) {
			giro -= 10.0f;
			printf("Posicion %f \n", giro);
			if (movAuto_x > -150) {
				movAuto_x -= 1.0f;
				printf("Posicion %f \n", movAuto_x);
			}
		}
		else {
			recorrido4 = false;
			recorrido5 = true;

		}
	}
	else if (recorrido5) {
		if (movAuto_z > -100) {
			movAuto_z -= 2.0f;
			printf("Posicion %f \n", movAuto_z);
			MovLLanta += 30.0f;
			printf("Posicion %f \n", MovLLanta);
		}
		else {
			recorrido5 = false;
			recorrido6 = true;
		}
	}
	else if (recorrido6) {
		if (giro > -270) {
			giro -= 10.0f;
			printf("Posicion %f \n", giro);
			if (movAuto_z > -110) {
				movAuto_z -= 1.0f;
				printf("Posicion %f \n", movAuto_x);
			}
		}
		else {
			recorrido6 = false;
			recorrido7 = true;
		}

	}
	else if (recorrido7) {
		if (movAuto_x < -10) {
			movAuto_x += 1.0f;
			printf("Posicion %f \n", movAuto_x);
		}
		else {
			recorrido7 = false;
			recorrido8 = true;
		}
	}
	else if (recorrido8) {
		if (giro > -360) {
			giro -= 10.0f;
			printf("Posicion %f \n", giro);
			if (movAuto_x < 0) {
				movAuto_x += 1.0f;
				printf("Posicion %f \n", movAuto_x);
			}
		}
		else {
			recorrido8 = false;
			recorrido9 = true;
		}
	}else if (recorrido9) {
		if (movAuto_z < 0) {
			movAuto_z += 1.0f;
			printf("Posicion %f \n", movAuto_z);
		}
		else {
			recorrido9 = false;
			movAuto_x = 0.0f;
			movAuto_z = 0.0f;
			giro = 0.0f;
			recorrido1 = true;
		}
	}
	//ANIMACIÓN PELOTA
	if (play)
	{
		rotx += 50.0f;
		if (posY < 15) {
			posY += 1.0f;
			posX += 1.0f;
			posZ += 1.0f;
			if (salto1 < 2) {
				salto1 += 0.5f;
			}
		}
		else if (posY < 25) {
				posY += 1.0f;
				posX += 1.0f;
				posZ += 1.0f;
				if (salto1 > 0) {
					salto1 -= 0.5f;
				}
				else {
					play = false;
					play2 = true;
				}
		}
	}
	else if (play2) {
		rotx += 50.0f;
		if (posY > 1.0f) {
			posY -= 1.0f;
			posX += 1.0f;
			posZ += 1.0f;
		}
		else {
			play2 = false;
			play3 = true;
		}
	}
	else if (play3) {
		rotx += 50.0f;
		if (posX > 0) {
			posX -= 1.0f;
			posZ -= 1.0f;
		}
		else {
			rotx = 0.0;
			posX = 0.0f;
			posZ = 0.0f;
			salto1 = 0.0f;
			play3 = false;
			play = true;
		}

		//ANIMACIÓN PERRO
	}if (adelante || valor != rotD)
		valor = rotD;
		if(rotD > 180.0) {
		var = rotD - 180;
		}
	else {
		var = rotD;
	}
	if (var > 90) {
		var -= 90;
		moDz += cos(var);
		moDx += (var / 90);
	}
	else if (var <= 90) {
		moDz += cos(var);
		moDx += (var / 90);
	}

	//avion

	if (recorrido_1)
	{
		movavion_z += 3.0f;
		orienta = 0.0f;
		if (movavion_z > 25.0f)
		{
			recorrido_1 = false;
			recorrido_2 = true;
		}
	}

	if (recorrido_2)
	{
		movavion_x -= 3.0f;
		movavion_z += 3.0f;
		orienta = -45.0f;
		if (movavion_x < -15.0f)
		{
			recorrido_2 = false;
			recorrido_3 = true;
		}
	}
	if (recorrido_3)
	{
		movavion_x -= 3.0f;
		orienta = -90.0f;
		if (movavion_x < -37.0f)
		{
			recorrido_3 = false;
			recorrido_4 = true;
		}
	}
	
	if (recorrido_4)
	{
		movavion_z -= 3.0f;
		movavion_x -= 3.0f;
		orienta = -135.0f;
		if (movavion_z < 25.0f)
		{
			recorrido_4 = false;
			recorrido_5 = true;
		}
	}
	if (recorrido_5)
	{
		movavion_z -= 3.0f;
		orienta = 180.0f;
		if (movavion_z < -25.0f)
		{
			recorrido_5 = false;
			recorrido_6 = true;
		}
	}
	
	if (recorrido_6)
	{
		movavion_x += 3.0f;
		movavion_z -= 3.0f;
		orienta = 135.0f;
		if (movavion_x > -37.0f)
		{
			recorrido_6 = false;
			recorrido_7 = true;
		}
	}
	if (recorrido_7)
	{
		movavion_x += 3.0f;
		orienta = 90.0f;
		if (movavion_x > -15.0f)
		{
			recorrido_7 = false;
			recorrido_8 = true;
		}
	}
	
	if (recorrido_8)
	{
		movavion_z += 3.0f;
		movavion_x += 3.0f;
		orienta = 45.0f;
		if (movavion_z > -25.0f)
		{
			recorrido_8 = false;
			recorrido_1 = true;
		}
	}
}

void display(Shader shader, Shader skyboxShader, GLuint skybox,
	Model arbol, Model base, Model perro, Model lambo, Model llanta,
	Model jeep,Model balon,Model persona,Model avion, Model casa,
	Model librero, Model cama, Model cama2, Model librero2)
{
	shader.use();

	//Setup Advanced Lights
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("dirLight.direction", lightDirection);
	shader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	shader.setVec3("pointLight[0].position", lightPosition);
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);
	shader.setFloat("pointLight[0].linear", 0.009f);
	shader.setFloat("pointLight[0].quadratic", 0.0000032f);

	shader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);
	shader.setFloat("pointLight[1].linear", 0.009f);
	shader.setFloat("pointLight[1].quadratic", 0.032f);

	shader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glm::mat4 temp01 = glm::mat4(1.0f);
	glm::mat4 tempArb = glm::mat4(1.0f);
	glm::mat4 tempCoche = glm::mat4(1.0f);
	glm::mat4 tempJeep = glm::mat4(1.0f);
	glm::mat4 tempcuerpo = glm::mat4(1.0f);
	glm::mat4 tempAvi = glm::mat4(1.0f);
	glm::mat4 tmpcasa = glm::mat4(1.0f);
	glm::mat4 tmpcama = glm::mat4(1.0f);
	glm::mat4 tmplibrero = glm::mat4(1.0f);
	glm::mat4 tmprecamara = glm::mat4(1.0f);

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	//-----------------------------------------------------------------------------------
	//										entorno
	//-----------------------------------------------------------------------------------
	model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, -15.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	base.Draw(shader);

	//variables a usar		j=valor de y/arriba			k=valor de x/lados		pos=valor de z/ adelante atras  rot= rotación
	int j = 0.0f, cont;
	float rot = 40.0f, k = -88.0f;
	
	//-----------------------------------------------------------------------------------
	//									ARBOLES
	//-----------------------------------------------------------------------------------
	//arbol
	model = glm::translate(tmp, glm::vec3(30.0f, 0.0f, 0.0f));
	tempArb = model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	arbol.Draw(shader);
	cont = 1;

	//Primera ilera arboles
	for (int i = 0; i < 16; i++)			//numero de arboles a agregar --9
	{
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		if (cont == 1) {
			model = glm::translate(tmp, glm::vec3(-28.0f, j, k));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		}

		else if (cont == 2) {
			model = glm::translate(tmp, glm::vec3(-3.0f, j, k));
			model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));

		}
		else if (cont == 3) {
			model = glm::translate(tmp, glm::vec3(-16.0f, j, k));
			model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));

		}
		else if (cont == 4) {
			model = glm::translate(tmp, glm::vec3(-32.0f, j, k));
			model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));

		}
		else if (cont == 5) {
			model = glm::translate(tmp, glm::vec3(-5.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (cont == 6) {
			model = glm::translate(tmp, glm::vec3(-20.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (cont == 7) {
			model = glm::translate(tmp, glm::vec3(-35.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (cont == 8) {
			model = glm::translate(tmp, glm::vec3(-28.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		shader.setMat4("model", model);
		arbol.Draw(shader);
		k = k + 15;
		rot = rot + 80;
		if (cont == 8) {
			cont = 1;
		}
		else
		{
			cont = cont + 1;
		}
	}
	//valores de inicio de regreso

	k = -96.0f;
	cont = 1;

	for (int i = 0; i < 15; i++)			//numero de arboles a agregar --9
	{
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		if (cont == 1) {
			model = glm::translate(tmp, glm::vec3(-40.0f, j, k));
			model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		}
		else if (cont == 2) {
			model = glm::translate(tmp, glm::vec3(-60.0f, j, k));
			model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));

		}
		else if (cont == 3) {
			model = glm::translate(tmp, glm::vec3(-50, j, k));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

		}
		else if (cont == 4) {
			model = glm::translate(tmp, glm::vec3(-45.0f, j, k));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));

		}
		else if (cont == 5) {
			model = glm::translate(tmp, glm::vec3(-58.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (cont == 6) {
			model = glm::translate(tmp, glm::vec3(-45.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (cont == 7) {
			model = glm::translate(tmp, glm::vec3(-55.0f, j, k));
			model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));

		}
		shader.setMat4("model", model);
		arbol.Draw(shader);
		k = k + 18;
		rot = rot + 80;

		if (cont == 7) {
			cont = 1;
		}
		else
		{
			cont = cont + 1;
		}
	}


	k = -88.0f;
	cont = 1;

	for (int i = 0; i < 10; i++)			//numero de arboles a agregar --9
	{
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		if (cont == 1) {
			model = glm::translate(tmp, glm::vec3(40.0f, j, k));
			model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		}
		else if (cont == 2) {
			model = glm::translate(tmp, glm::vec3(18.0f, j, k));
			model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));

		}
		else if (cont == 3) {
			model = glm::translate(tmp, glm::vec3(4.0f, j, k));
			model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));

		}
		else if (cont == 4) {
			model = glm::translate(tmp, glm::vec3(10.0f, j, k));
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));

		}
		else if (cont == 5) {
			model = glm::translate(tmp, glm::vec3(20.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (cont == 6) {
			model = glm::translate(tmp, glm::vec3(28.0f, j, k));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		else if (cont == 7) {
			model = glm::translate(tmp, glm::vec3(15.0f, j, k));
			model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));

		}
		shader.setMat4("model", model);
		arbol.Draw(shader);
		k = k + 10;
		rot = rot + 80;

		if (cont == 7) {
			cont = 1;
		}
		else
		{
			cont = cont + 1;
		}
	}




	//-------------------------------------------------------------------------------------------------
	//											CASA
	//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmpcasa, glm::vec3(0.0f, 1.0f, 25.0f));
	//model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	casa.Draw(shader);

	//-------------------------------------------------------------------------------------------------
	//											CAMA
	//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmpcama, glm::vec3(2.0f, 1.0f, 29.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	cama.Draw(shader);

	//-------------------------------------------------------------------------------------------------
	//											LIBRERO
	//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmplibrero, glm::vec3(8.0f, 0.0f, 28.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	librero.Draw(shader);

	//-------------------------------------------------------------------------------------------------
	//											CAMA2
	//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmprecamara, glm::vec3(-14.0f, 1.0f, 28.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	//model = glm::scale(tmprecamara, glm::vec3(2.0f, 0.0f, 2.0f));
	shader.setMat4("model", model);
	cama2.Draw(shader);

	//-------------------------------------------------------------------------------------------------
	//											LIBRERO2
	//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmprecamara, glm::vec3(-4.5f, 4.0f, 28.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	//model = glm::scale(tmprecamara, glm::vec3(2.0f, 0.0f, 2.0f));
	shader.setMat4("model", model);
	librero2.Draw(shader);

//-------------------------------------------------------------------------------------------------
//											PERRO
//-------------------------------------------------------------------------------------------------
	model = glm::rotate(model, glm::radians(rotD), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(tmp, glm::vec3(moDx, 0.3f, moDz));
	model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));

	shader.setMat4("model", model);
	perro.Draw(shader);



//-------------------------------------------------------------------------------------------------
//											PERSONA
//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmp, glm::vec3(30.0f, salto1, 30.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	persona.Draw(shader);


	model = glm::translate(tmp, glm::vec3(56.0f, salto2, 56.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	persona.Draw(shader);
//-------------------------------------------------------------------------------------------------
//											BALON
//-------------------------------------------------------------------------------------------------
	model = glm::translate(tmp, glm::vec3(30.0f+posX,posY,30.0f+posZ));
	model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
	model = glm::rotate(model, glm::radians(rotx), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	balon.Draw(shader);

//-------------------------------------------------------------------------------------------------
//											AVION
//-------------------------------------------------------------------------------------------------
	model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(10.0f + movavion_x, 70.0f + movavion_y, 10.0f + movavion_z));
	tempAvi = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));

	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	avion.Draw(shader);
	
//-------------------------------------------------------------------------------------------------
//											JEEP
//-------------------------------------------------------------------------------------------------

	//jeep 1
	model = glm::translate(tmp, glm::vec3(MovJeepx,0.5f, 160.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	jeep.Draw(shader);

	//jeep2
	model = glm::translate(tmp, glm::vec3(MovJeepx, 0.5f, -105.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	jeep.Draw(shader);	

//-------------------------------------------------------------------------------------------------
//											LAMBO
//-------------------------------------------------------------------------------------------------
model = glm::translate(tmp, glm::vec3(78.0f+movAuto_x,0.5f, movAuto_z));
tempCoche= model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0));
model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
shader.setMat4("model", model);
lambo.Draw(shader);

model = glm::translate(tempCoche, glm::vec3(0.85f, 0.25f, 1.29f));
model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
model = glm::rotate(model, glm::radians(MovLLanta), glm::vec3(1.0f, 0.0f, 0.0f));
shader.setMat4("model", model);
llanta.Draw(shader);	//Izq delantera

model = glm::translate(tempCoche, glm::vec3(-0.85f, 0.25f, 1.29f));
model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
model = glm::rotate(model, glm::radians(MovLLanta), glm::vec3(1.0f, 0.0f, 0.0f));
shader.setMat4("model", model);
llanta.Draw(shader);	//Der delantera

model = glm::translate(tempCoche, glm::vec3(-0.85f, 0.25f, -1.45f));
model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
model = glm::rotate(model, glm::radians(MovLLanta), glm::vec3(1.0f, 0.0f, 0.0f));
shader.setMat4("model", model);
llanta.Draw(shader);	//Der trasera

model = glm::translate(tempCoche, glm::vec3(0.85f, 0.25f, -1.45f));
model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
model = glm::rotate(model, glm::radians(MovLLanta), glm::vec3(1.0f, 0.0f, 0.0f));
shader.setMat4("model", model);
llanta.Draw(shader);	//Izq trase


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
	//piso
	glBindVertexArray(VAO);
	//Colocar código aquí
	//shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	//shader.setInt("texture1",0);
	glBindTexture(GL_TEXTURE_2D, t_piso);
	//glDrawArrays(GL_QUADS, 0, 24);
	// Draw skybox as last
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	skyboxShader.use();
	view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set depth function back to default
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Teoria", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, my_input);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();

	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	myData2();
	glEnable(GL_DEPTH_TEST);
	//Shaders
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

	// Load models
	Model casa = ((char *)"NexModels/casa/casa.obj");
	Model librero = ((char *)"NexModels/LibreroCompleto/mesa.obj");
	Model cama = ((char *)"NexModels/Camalista1/cama1.obj");
	Model cama2 = ((char *)"NexModels/Camalista2/cama2.obj");
	Model librero2 = ((char *)"NexModels/LibreroCompleto2/librero2.obj");
	Model base = ((char *)"NexModels/base/city.obj");
	Model arbol = ((char *)"NexModels/arbol/arbol2.obj");
	Model perro = ((char *)"NexModels/Perro/perroncho.obj");
	Model lambo = ((char *)"NexModels/Lambo/Carroseria.obj");
	Model llanta = ((char *)"NexModels/Lambo/Wheel.obj");
	Model jeep = ((char *)"NexModels/jeep/jeep.obj");
	Model balon= ((char *)"NexModels/balon/Basket.obj");
	Model persona = ((char *)"NexModels/persona1/persona.obj");
	Model avion = ((char *)"NexModels/avion/plane.obj");

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
      
		animate();

        // render
        // Background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, SkyBoxshader, cubemapTexture,
			
				arbol, base, perro, lambo, llanta, jeep,
				balon,persona,avion, casa, librero, cama,
				cama2, librero2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
		
    }
   //glfw: terminate, clearing all previously allocated GLFW reso	PlaySound(TEXT("audio/halo1.wav"), NULL, SND_SYNC);sources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode){

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		adelante =true;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		adelante = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (rotD < 360) {
			rotD += 10.0f;
		}
		else if (rotD = 360) {
			rotD = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (rotD < 360) {
			rotD -= 10.0f;
		}
		else if (rotD = 360) {
			rotD = 0.0f;
		}
	}
}


void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}