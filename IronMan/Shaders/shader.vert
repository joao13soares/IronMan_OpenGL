#version 430 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 ModelView;		// View * Model
uniform mat4 Projection;
uniform mat3 NormalMatrix;

in vec3 vPosition;			// Coordenadas locais do v�rtice
in vec3 vColor;				// Cor do v�rtice
in vec2 vTexture;			// Coordenada de textura do v�rtice
in vec3 vNormal;			// Normal do v�rtice

out vec3 vPositionEyeSpace;
out vec3 colorCoord;
out vec2 textureCoord;
out vec3 vNormalEyeSpace;

layout(location = 0) uniform float time;

void main()
{ 
	// Posi��o do v�rtice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vPosition, 1.0)).xyz;
	
	// Coordenada de cor
	colorCoord = vColor;

	// Coordenada de textura
	textureCoord = vTexture;

	// Transformar a normal do v�rtice.
	vNormalEyeSpace = normalize(NormalMatrix * vNormal);

	// model distortion no eixo vertical
	vec3 newVPosition = vec3(vPosition.x, vPosition.y * abs(sin(time)), vPosition.z);

	// Posi��o final do v�rtice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(newVPosition, 1.0f);
}
