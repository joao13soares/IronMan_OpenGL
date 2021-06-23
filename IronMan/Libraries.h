#pragma once

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

// Tipos de dados:
// vec3, vec4, ivec4, mat4, entre outros.
#include <glm/glm.hpp>
// Fun��es de matrizes de transforma��o:
// translate, rotate, scal, frustum, perspective, ortho, entre outras.
#include <glm/gtc/matrix_transform.hpp>
// Fun��es que manipulam a intera��o entre apontadores e tipos de vectores e matrizes
// value_ptr
#include <glm/gtc/type_ptr.hpp>

#include <glm\gtc\matrix_inverse.hpp> // glm::inverseTranspose()

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL/gl.h>

#define GLFW_USE_DWM_SWAP_INTERVAL
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;