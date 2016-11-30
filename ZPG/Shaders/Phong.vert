#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec3 worldPosition;
out vec3 worldNormal;
out vec2 texCoord;
out vec3 worldTangent;
out vec3 worldBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = (projection * view * model) * vec4(position, 1.0);

	worldPosition = vec3(model * vec4(position, 1.0));
	mat3 m = transpose(inverse(mat3(model)));
	worldNormal = normalize(m * normal);
	texCoord = textureCoord;
	worldTangent = normalize(m * tangent);
	worldBitangent = normalize(m * bitangent);
};