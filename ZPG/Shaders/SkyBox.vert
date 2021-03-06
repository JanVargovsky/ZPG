#version 330 core
layout(location = 0) in vec3 position;

out vec3 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = (projection * mat4(mat3(view)) * model) * vec4(position, 1.0f);
	texCoord = position;
};