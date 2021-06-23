#pragma once

#include "Libraries.h"
#include "ModelDataManager.h"
#include "Camera.h"
#include "LoadShaders.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct LightEnablers {
	bool key1AlreadyPressed;
	bool ambientLightEnabler;

	bool key2AlreadyPressed;
	bool directionalLightEnabler;

	bool key3AlreadyPressed;
	bool pointLightEnabler;

	bool key4AlreadyPressed;
	bool spotLightEnabler;

};

LightEnablers lightEnablers = { false, true, 
								false, true, 
								false, true, 
								false, true, };

void lightEnabling(GLFWwindow *window);
void updateDeltaTime();
void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void print_error(int error, const char *description);
void init(VectorsData vectorsData, MaterialData materialData);
void load_texture(string textureFilePath);
void display(void);

#define WIDTH 800
#define HEIGHT 600

GLfloat ZOOM = 10.0f;
GLfloat ANGLE = 0.0f;

#define NumVAOs 1
#define NumBuffers 4 // Vertices, Colors, Textures, Normals
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 9264;

GLuint programa;

glm::mat4 Model, View, Projection;
glm::mat3 NormalMatrix;
GLfloat angle = 0.0f;

float deltaTime = 0.0f;
float previousTime = 0.0f;

Camera camera;

int main(void) {
	ModelDataManager modelDataManager("Iron_Man.xyz");

	GLFWwindow *window;

	glfwSetErrorCallback(print_error);

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "P3D - Trabalho Pratico IronMan", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Inicia o gestor de extensões GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// load texture
	load_texture(modelDataManager.getTextureFilePath());

	init(modelDataManager.getVectorsData(), modelDataManager.getMaterialData());

	//glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// "desligar" mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// atribuir valor time para model distortion
	float time = float(glfwGetTime());
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "time"), time);

	while (!glfwWindowShouldClose(window)) {
		// update deltaTime
		updateDeltaTime();
		// update cameraDeltaTime
		camera.updateCameraDeltaTime(deltaTime);
		// printCameraInfo
		//camera.printInfo();

		// Light Enabling
		lightEnabling(window);

		// atualizar valor time para model distortion
		time = float(glfwGetTime());
		glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "time"), time);

		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void lightEnabling(GLFWwindow *window) {
	// ambientLightEnabler
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !lightEnablers.key1AlreadyPressed) {
		lightEnablers.ambientLightEnabler = !lightEnablers.ambientLightEnabler;
		glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.ambientLightEnabler"), lightEnablers.ambientLightEnabler);
		lightEnablers.key1AlreadyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_1) != GLFW_PRESS && lightEnablers.key1AlreadyPressed)
		lightEnablers.key1AlreadyPressed = false;

	// directionalLightEnabler
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !lightEnablers.key2AlreadyPressed) {
		lightEnablers.directionalLightEnabler = !lightEnablers.directionalLightEnabler;
		glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.directionalLightEnabler"), lightEnablers.directionalLightEnabler);
		lightEnablers.key2AlreadyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_2) != GLFW_PRESS && lightEnablers.key2AlreadyPressed)
		lightEnablers.key2AlreadyPressed = false;

	// pointLightEnabler
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !lightEnablers.key3AlreadyPressed) {
		lightEnablers.pointLightEnabler = !lightEnablers.pointLightEnabler;
		glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.pointLightEnabler"), lightEnablers.pointLightEnabler);
		lightEnablers.key3AlreadyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_3) != GLFW_PRESS && lightEnablers.key3AlreadyPressed)
		lightEnablers.key3AlreadyPressed = false;

	// spotLightEnabler
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !lightEnablers.key4AlreadyPressed) {
		lightEnablers.spotLightEnabler = !lightEnablers.spotLightEnabler;
		glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.spotLightEnabler"), lightEnablers.spotLightEnabler);
		lightEnablers.key4AlreadyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_4) != GLFW_PRESS && lightEnablers.key4AlreadyPressed)
		lightEnablers.key4AlreadyPressed = false;
}

void updateDeltaTime() {
	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - previousTime);
	previousTime = currentTime;
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
	camera.cursorPosCallback(window, xpos, ypos);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	camera.keyCallback(window, key, scancode, action, mods);
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.scrollCallback(window, xoffset, yoffset);
}

void print_error(int error, const char *description) {
	cout << description << endl;
}

void init(VectorsData vectorsData, MaterialData materialData) {
	// ****************************************************
	// Criar arrays de dados na RAM
	// ****************************************************

	/*glm::vec3 colors[NumVertices];
	for (int i = 0; i < NumVertices; i++)
	{
		colors[i] = { 1.0f, 1.0f, 1.0f };
	}*/

	// ****************************************************
	// VAOs - Vertex Array Objects
	// ****************************************************

	// Gerar 'NumVAOs' nomes para VAOs.
	// Neste caso, como NumVAOS = 1, gera apenas 1 nome.
	glGenVertexArrays(NumVAOs, VAOs);
	// Faz bind do VAO, cujo nome está definido em 'VAOs[0]', com o contexto do OpenGL.
	// Um VAO é criado no primero bind que lhe seja feito.
	// Este VAO passa a estar ativo até que seja feito o bind a outro VAO, ou seja feito o bind com valor 0.
	glBindVertexArray(VAOs[0]);

	// ****************************************************
	// VBOs - Vertex Buffer Objects
	// ****************************************************

	// Gera 'NumBuffers' nomes para VBOs.
	// Neste caso, como NumBuffers = 2, gera 2 nomes
	// Esta função pode ser chamada antes da criação de VAOs.
	glGenBuffers(NumBuffers, Buffers);
	// Para cada nome de VBO
	for (int i = 0; i < NumBuffers; i++) {
		// Faz bind do VBO ao buffer GL_ARRAY_BUFFER.
		// GL_ARRAY_BUFFER é utilizado para dados de atributos de vértices.
		// Um VBO é criado no primeiro bind que lhe seja feito.
		// Este VBO passa a estar ativo até que seja feito o bind a outro VBO ou seja feito o bind com valor 0.
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
		if (i == 0) {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, glm::value_ptr(vectorsData.v[0]), 0);
			// Inicializa o VBO (que está ativo) com memória de tamanho mutável.
			//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, glm::value_ptr(v[0]), GL_STATIC_DRAW);
		}
		/*else if (i == 1) {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, colors, 0);
			// Inicializa o VBO (que está ativo) com memória de tamanho mutável.
			//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, colors, GL_STATIC_DRAW);
		}*/
		else if (i == 2) {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec2) * NumVertices, glm::value_ptr(vectorsData.vt[0]), 0);
			// Inicializa o VBO (que está ativo) com memória de tamanho mutável.
			//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * NumVertices, glm::value_ptr(vt[0]), GL_STATIC_DRAW);
		}
		else if (i == 3) {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, glm::value_ptr(vectorsData.vn[0]), 0);
			// Inicializa o VBO (que está ativo) com memória de tamanho mutável.
			//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * NumVertices, glm::value_ptr(vn[0]), GL_STATIC_DRAW);
		}
	}

	// ****************************************************
	// Shaders
	// ****************************************************

	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER,   "Shaders\\shader.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders\\shader.frag" },
		{ GL_NONE, NULL }
	};

	programa = LoadShaders(shaders);
	if (!programa) exit(EXIT_FAILURE);
	glUseProgram(programa);

	// ****************************************************
	// Ligar Atributos aos Shaders
	// ****************************************************

	// As localizações de atributos fazem parte do programa shader, e são completamente independentes do VAO.
	// Podemos, assim, obter as localizações de atributos sem que antes se tenha criado qualquer VAO.
	// ------------------------------------------------------------------------------------------------------
	// Obtém a localização do atributo 'vPosition' no 'programa'.
	//GLint coordsId = glGetAttribLocation(programa, "vPosition"); // Para versões anteriores à 4.3
	GLint coordsId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition"); // Para versões >= 4.3
	// Obtém a localização do atributo 'vColors' no 'programa'.
	//GLint coresId = glGetAttribLocation(programa, "vColors"); // Para versões anteriores à 4.3
	GLint coresId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vColor"); // Para versões >= 4.3
	// Obtém a localização do atributo 'vTextureCoords' no 'programa'.
	//GLint texturaId = glGetAttribLocation(programa, "vTextureCoords"); // Para versões anteriores à 4.3
	GLint texturaId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vTexture"); // Para versões >= 4.3
	// Obtém a localização do atributo 'vNormal' no 'programa'.
	//GLint normalId = glGetAttribLocation(programa, "vNormal"); // Para versões anteriores à 4.3
	GLint normalId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vNormal"); // Para versões >= 4.3

	//glBindVertexArray(VAOs[0]); // Não é necessário fazer o bind do VAO, pois ele já é o que está ativo no contexto do OpenGL.

	// Ativa o VBO 'Buffers[0]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	// Liga a localização do atributo 'vPosition' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'coordsId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 3 elementos do tipo float.
	glVertexAttribPointer(coordsId, 3 /*3 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

	// Ativa o VBO 'Buffers[1]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	// Liga a localização do atributo 'vColors' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'coordsId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 3 elementos do tipo float.
	glVertexAttribPointer(coresId, 3 /*3 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

	// Ativa o VBO 'Buffers[2]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
	// Liga a localização do atributo 'vTextureCoords' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'texturaId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 2 elementos do tipo float.
	glVertexAttribPointer(texturaId, 2 /*2 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

	// Ativa o VBO 'Buffers[3]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[3]);
	// Liga a localização do atributo 'vNormal' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'normalId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 3 elementos do tipo float.
	glVertexAttribPointer(normalId, 3 /*3 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);


	// Indicação da Unidade de Textura a ligar ao sampler 'TexSampler'.
	//glUniform1i(glGetUniformLocation(programa, "TexSampler"), 0 /* Unidade de Textura #0 */);
	GLint locationTexSampler = glGetProgramResourceLocation(programa, GL_UNIFORM, "TexSampler");
	glProgramUniform1i(programa, locationTexSampler, 0 /* Unidade de Textura #0 */);


	// Habitita o atributo com localização 'coresId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(coordsId);
	// Habitita o atributo com localização 'coresId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(coresId);
	// Habitita o atributo com localização 'texturaId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(texturaId);
	// Habitita o atributo com localização 'normalId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(normalId);

	// ****************************************************
	// Matrizes de transformação
	// ****************************************************

	Projection = glm::perspective(glm::radians(camera.FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		camera.position,					// eye (posição da câmara). Câmara na posição (x=0, y=0, z=5). Nota que movo o mundo em sentido contrário.
		camera.position + camera.direction,	// center (para onde está a "olhar")
		camera.up							// up
	);
	Model = glm::rotate(glm::mat4(1.0f), angle += 0.002f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ModelView = View * Model;
	NormalMatrix = glm::inverseTranspose(glm::mat3(ModelView));

	// ****************************************************
	// Uniforms
	// ****************************************************

	// Atribui valor ao uniform Model
	GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, glm::value_ptr(Model));
	// Atribui valor ao uniform View
	GLint viewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(programa, viewId, 1, GL_FALSE, glm::value_ptr(View));
	// Atribui valor ao uniform ModelView
	GLint modelViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(programa, modelViewId, 1, GL_FALSE, glm::value_ptr(ModelView));
	// Atribui valor ao uniform Projection
	GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, glm::value_ptr(Projection));
	// Atribui valor ao uniform NormalMatrix
	GLint normalViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix3fv(programa, normalViewId, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	// Ambient Light
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));

	// Directional Light
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));

	// Point Light #1
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].constant"), 1.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].linear"), 0.06f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].quadratic"), 0.02f);

	// Point Light #2
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].position"), 1, glm::value_ptr(glm::vec3(-2.0, 2.0, 5.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].constant"), 1.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].linear"), 0.06f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].quadratic"), 0.02f);

	// Spot Light
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.position"), 1, glm::value_ptr(camera.position));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.constant"), 1.0f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.linear"), 0.06f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.quadratic"), 0.02f);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotCutoff"), glm::cos(glm::radians(17.5f)));
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotExponent"), glm::cos(glm::radians(12.0f)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "spotLight.spotDirection"), 1, glm::value_ptr(camera.direction));

	// Material
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(materialData.Ka)); // (Ka)
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(materialData.Kd)); // (Kd)
	glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(materialData.Ks)); // (Ks)
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.shininess"), materialData.Ns); // (Ns)

	// LightEnablers
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.ambientLightEnabler"), lightEnablers.ambientLightEnabler);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.directionalLightEnabler"), lightEnablers.directionalLightEnabler);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.pointLightEnabler"), lightEnablers.pointLightEnabler);
	glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "lightEnablers.spotLightEnabler"), lightEnablers.spotLightEnabler);

	// ****************************************************
	// Definir a janela de visualização (viewport)
	// ****************************************************

	glViewport(0, 0, WIDTH, HEIGHT);
}

void load_texture(string textureFilePath) {
	GLuint textureName = 0;

	// Gera um nome de textura
	glGenTextures(1, &textureName);

	// Ativa a Unidade de Textura #0
	// A Unidade de Textura 0 já está ativa por defeito.
	// Só uma Unidade de Textura está ativa a cada momento.
	glActiveTexture(GL_TEXTURE0);

	// Vincula esse nome de textura ao target GL_TEXTURE_2D da Unidade de Textura ativa.
	glBindTexture(GL_TEXTURE_2D, textureName);

	// Define os parâmetros de filtragem (wrapping e ajuste de tamanho)
	// para a textura que está vinculada ao target GL_TEXTURE_2D da Unidade de Textura ativa.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Leitura/descompressão do ficheiro com imagem de textura
	int width, height, nChannels;
	// Ativa a inversão vertical da imagem, aquando da sua leitura para memória.
	stbi_set_flip_vertically_on_load(true);
	// Leitura da imagem para memória do CPU
	unsigned char *imageData = stbi_load(textureFilePath.c_str(), &width, &height, &nChannels, 0);
	if (imageData) {
		// Carrega os dados da imagem para o Objeto de Textura vinculado ao target GL_TEXTURE_2D da Unidade de Textura ativa.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);

		// Gera o Mipmap para essa textura
		glGenerateMipmap(GL_TEXTURE_2D);

		// Liberta a imagem da memória do CPU
		stbi_image_free(imageData);
	}
	else {
		cout << "Error loading texture!" << endl;
	}
}

void display(void) {
	static const float black[] = {
		0.0f, 0.0f, 0.0f, 0.0f
	};

	// A função glClearBufferfv(GL_COLOR, ...) é semelhante à função glClearColor().
	glClearBufferfv(GL_COLOR, 0, black);

	// Limpa o buffer de profundidade
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ****************************************************
	// Outros parâmetros do OpenGL
	// ****************************************************

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
	glCullFace(GL_BACK); // GL_FRONT, [GL_BACK], GL_FRONT_AND_BACK

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs();
	// Atualiza os dados do Uniform
	Projection = glm::perspective(glm::radians(camera.FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		camera.position,					// eye (posição da câmara). Câmara na posição (x=0, y=0, z=5). Nota que movo o mundo em sentido contrário.
		camera.position + camera.direction,	// center (para onde está a "olhar")
		camera.up							// up
	);
	Model = glm::rotate(glm::mat4(1.0f), angle += 0.002f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ModelView = View * Model;
	NormalMatrix = glm::inverseTranspose(glm::mat3(ModelView));
	// Atualiza o valor ao uniform Model
	GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, glm::value_ptr(Model));
	// Atualiza o valor ao uniform View
	GLint viewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(programa, viewId, 1, GL_FALSE, glm::value_ptr(View));
	// Atualiza o valor ao uniform ModelView
	GLint modelViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(programa, modelViewId, 1, GL_FALSE, glm::value_ptr(ModelView));
	// Atualiza o valor ao uniform Projection
	GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, glm::value_ptr(Projection));
	// Atualiza o valor ao uniform NormalMatrix
	GLint normalViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix3fv(programa, normalViewId, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	// Vincula (torna ativo) o VAO
	glBindVertexArray(VAOs[0]);
	// Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}
