#version 330 core
in vec3 worldPosition;
in vec3 worldNormal;

out vec4 outColor;

/*
uniform sampler2D textureX;
uniform sampler2D textureY;
uniform sampler2D textureZ;
uniform sampler2D textureHighX;
uniform sampler2D textureHighY;
uniform sampler2D textureHighZ;
*/

uniform sampler2D textureTerrainLow;
uniform sampler2D textureTerrainNormal;
uniform sampler2D textureTerrainHigh;

vec4 calculateTexture(vec2 pos, float height);

void main()
{
	vec3 blendWeights = abs(worldNormal);
	blendWeights = max(blendWeights, 0.0001);
	blendWeights = pow(blendWeights, vec3(1, 5, 1));

	blendWeights /= (blendWeights.x + blendWeights.y + blendWeights.z);

	float scale = 0.5f;
	float height = worldPosition.y;
	vec4 axisX = calculateTexture(worldPosition.yz * scale, worldPosition.y);
	vec4 axisY = calculateTexture(worldPosition.xz * scale, worldPosition.y);
	vec4 axisZ = calculateTexture(worldPosition.xy * scale, worldPosition.y);

	outColor = axisX*blendWeights.x + axisY*blendWeights.y + axisZ*blendWeights.z;

	//outColor = vec4(abs(worldNormal), 1.0f);
	//outColor = vec4(color, 1.0f);
};

vec4 calculateTexture(vec2 pos, float height)
{
	float t = 0.5f;
	float l1 = -2.f, l2 = 3.f;

	vec4 result = mix(texture(textureTerrainLow, pos), texture(textureTerrainNormal, pos), smoothstep(l1 - t, l1 + t, height));
	result = mix(result, texture(textureTerrainHigh, pos), smoothstep(l2 - t, l2 + t, height));

	return result;
}