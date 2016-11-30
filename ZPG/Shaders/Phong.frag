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
in vec3 worldTangent;
in vec3 worldBitangent;

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
uniform sampler2D textureNormal;

// Functions
vec3 calcNormal();
vec3 calcPointLight();
vec3 calcSpotLight();

vec3 normal;

void main()
{
	normal = calcNormal();

	vec3 c = calcPointLight() + calcSpotLight();
	outColor = texture(textureDiffuse, texCoord) * vec4(c, 1.0);
};

vec3 calcNormal()
{
	vec3 Normal = normalize(worldNormal);
	vec3 Tangent = normalize(worldTangent);
	//Gram–Schmidt process
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
	vec3 Bitangent = cross(Tangent, Normal);

	vec3 mappedNormal = texture(textureNormal, texCoord).xyz;
	mappedNormal = mappedNormal * 2.0f - 1.0f;

	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	return normalize(TBN * mappedNormal);


	// Normal mapping
	//vec3 mappedNormal = texture(textureNormal, texCoord).xyz;
	//mappedNormal = normal * 2.0f - 1.0f;

	//mat3 TBN = mat3(worldTangent, worldBitangent, mappedNormal);
	//return normalize(TBN * mappedNormal);

}

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
		vec3 R = reflect(-L, normal);

		float dotProductLN = max(dot(L, normal), 0.0f);
		float dotProductVR = max(dot(V, R), 0);

		diffuse += (pointLights[i].attenuation * I_L * vec3(dotProductLN));
		specular += (pointLights[i].attenuation * I_L * R_S * vec3(pow(dotProductVR, h)));
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
			vec3 R = reflect(-L, normal);

			float dotProductLN = max(dot(L, normal), 0.0f);

			result += (spotLights[i].attenuation * vec3(dotProductLN));
		}
	}
	return result;
}
