#version 330 core
in vec2 texCoord;

out vec4 color;

uniform sampler2D skyDomeTexture;

void main()
{
	vec2 newTexCoords = vec2(abs(texCoord.x), abs(texCoord.y));
	color = texture(skyDomeTexture, newTexCoords);
}