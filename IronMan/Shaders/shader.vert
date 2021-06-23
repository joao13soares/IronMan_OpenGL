#version 430 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 ModelView;		// View * Model
uniform mat4 Projection;
uniform mat3 NormalMatrix;

in vec3 vPosition;			// Coordenadas locais do vértice
in vec3 vColor;				// Cor do vértice
in vec2 vTexture;			// Coordenada de textura do vértice
in vec3 vNormal;			// Normal do vértice

out vec3 vPositionEyeSpace;
out vec3 colorCoord;
out vec2 textureCoord;
out vec3 vNormalEyeSpace;

layout(location = 0) uniform float time;

void main()
{ 
	// Posição do vértice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vPosition, 1.0)).xyz;
	
	// Coordenada de cor
	colorCoord = vColor;

	// Coordenada de textura
	textureCoord = vTexture;

	// Transformar a normal do vértice.
	vNormalEyeSpace = normalize(NormalMatrix * vNormal);

	// model distortion no eixo vertical
	vec3 newVPosition = vec3(vPosition.x, vPosition.y * abs(sin(time)), vPosition.z);

	// Posição final do vértice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(newVPosition, 1.0f);
}
