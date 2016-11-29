#version 330 core
in vec3 texCoord;

out vec4 color;

uniform samplerCube textureCube;

void main()
{
	color = texture(textureCube, texCoord);
}