#version 330 core
in vec2 texCoord;

out vec4 color;

uniform sampler2D skyDomeTexture;

void main()
{
	vec2 newTexCoords = vec2(0.5 + texCoord.x, 0.5 + texCoord.y);
	//if (texCoord.x < 0 || texCoord.y < 0 || texCoord.x > 1 || texCoord.y > 1)
	if (newTexCoords.x < 0 || newTexCoords.y < 0 || newTexCoords.x > 1 || newTexCoords.y > 1)
		color = vec4(1,0,0,0);
	else
		color = texture(skyDomeTexture, newTexCoords);
}