#version 330 core

struct PointLight {
	vec3 position;
	float attenuation;
};

struct SpotLight {
	vec3 position;
	float attenuation;
	vec3 direction;
	float radius;
};

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 texCoord;

out vec4 outColor;

uniform vec3 color;
uniform vec3 cameraPosition;

// Lights
// Point light
uniform PointLight pointLights[4];
uniform int pointLightCount = 0;
// Spot light
uniform SpotLight spotLights[4];
uniform int spotLightCount = 0;

// Textures
uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

// Functions
vec3 calcPointLight();
vec3 calcSpotLight();

void main()
{
	vec3 c = calcPointLight() + calcSpotLight();
	outColor = texture(textureDiffuse, texCoord) * vec4(c, 1.0);
};

vec3 calcPointLight()
{
	const float I_L = 0.2;
	const float I_A = 1;
	const float R_A = 0.3;
	const float R_S = 10;
	const float h = 20;

	vec3 V = normalize(cameraPosition - worldPosition);

	vec3 ambient = vec3(I_A * R_A, I_A * R_A, I_A * R_A);
	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 L = normalize(pointLights[i].position - worldPosition);
		vec3 R = reflect(-L, worldNormal);

		float dotProductLN = max(dot(L, worldNormal), 0.0f);
		float dotProductVR = max(dot(V, R), 0);

		diffuse += (I_L * vec3(dotProductLN));
		specular += (I_L * R_S * vec3(pow(dotProductVR, h)));
	}
	return (ambient + diffuse + specular);
}

vec3 calcSpotLight()
{
	vec3 result = vec3(0);
	for (int i = 0; i < spotLightCount; i++)
	{
		// vector from light's position to fragment
		vec3 L = normalize(spotLights[i].position - worldPosition);
		float angle = dot(-L, spotLights[i].direction);
		if (angle >= spotLights[i].radius)
		{
			vec3 R = reflect(-L, worldNormal);

			float dotProductLN = max(dot(L, worldNormal), 0.0f);

			result += (spotLights[i].attenuation * vec3(dotProductLN));
		}
	}
	return result;
}
