#version 330 core
in vec3 worldPosition;
in vec3 worldNormal;

out vec4 outColor;

uniform vec3 color;

uniform sampler2D textureX;
uniform sampler2D textureY;
uniform sampler2D textureZ;

void main()
{
	float scale = 0.5;
	vec3 blendWeights = abs(worldNormal);
	blendWeights = max(blendWeights - 0.2, 0); //max 1/odm(3)=0.577350
	blendWeights = pow(blendWeights, vec3(1, 5, 1));

	blendWeights /= (blendWeights.x + blendWeights.y + blendWeights.z);

	vec4 cXY = texture(textureX, worldPosition.xy * scale);
	vec4 cXZ = texture(textureY, worldPosition.xz * scale);
	vec4 cYZ = texture(textureZ, worldPosition.yz * scale);

	outColor = cXY*blendWeights.z + cXZ*blendWeights.y + cYZ*blendWeights.x;

	//outColor = vec4(worldNormal, 1.0f);
	//outColor = vec4(color, 1.0f);
};