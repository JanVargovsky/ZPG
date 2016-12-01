#version 330 core

struct PointLight {
	vec3 position;
};

struct SpotLight {
	vec3 position;
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
float calcAttenuation(vec3 lightPosition, vec3 fragmentPosition);
vec3 calcLight(PointLight light);
vec3 calcLight(SpotLight light);
vec3 calcColor();

vec3 normal;

void main()
{
	normal = calcNormal();
	outColor = vec4(calcColor(), 1.0f);
	//if (abs(dot(worldNormal, worldTangent)) >= 0.1 || abs(dot(worldBitangent, worldTangent)) >= 0.1 || abs(dot(worldNormal, worldBitangent)) >= 0.1)
 //   {
 //       outColor = vec4(1, 0, 0, 0);
 //   }
};

vec3 calcNormal()
{
	bool useBumpMapping = true;
	if (useBumpMapping)
	{
		// Normal mapping
		vec3 mappedNormal = texture(textureNormal, texCoord).xyz;
		mappedNormal = mappedNormal * 2.0f - 1.0f;

		mat3 TBN = mat3(worldBitangent, worldTangent, worldNormal);
		return normalize(TBN * mappedNormal);
	}
	else
		return worldNormal;
}

vec3 calcColor()
{
	vec3 result = vec3(0.0);

	for (int i = 0; i < pointLightCount; i++)
		result += calcLight(pointLights[i]);

	for (int i = 0; i < spotLightCount; i++)
		result += calcLight(spotLights[i]);

	return result;
}

float calcAttenuation(vec3 lightPosition, vec3 fragmentPosition)
{
	float d = length(lightPosition - fragmentPosition);
	const float K_C = 1.0f;
	const float K_L = 0.09f;
	const float K_Q = 0.032f;
	float attenuation = 1.f / (1.0 + K_C * d + K_Q * d * d);
	return attenuation;
}

vec3 calcLight(PointLight light)
{
	const float h = 20;

	vec3 ambient = vec3(0);
	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	vec3 V = normalize(cameraPosition - worldPosition);
	vec3 L = normalize(light.position - worldPosition);
	vec3 R = reflect(-L, normal);

	float dotProductLN = max(dot(L, normal), 0.0f);
	float dotProductVR = max(dot(V, R), 0);

	float attenuation = calcAttenuation(light.position, worldPosition);

	ambient += (attenuation * vec3(0.5));
	diffuse += (attenuation * vec3(dotProductLN));
	specular += (attenuation * vec3(pow(dotProductVR, h)));

	return vec3(texture(textureDiffuse, texCoord)) * ambient +
		vec3(texture(textureDiffuse, texCoord)) * diffuse +
		vec3(texture(textureSpecular, texCoord)) * specular;
}

vec3 calcLight(SpotLight light)
{
	const float h = 20;

	vec3 ambient = vec3(0);
	vec3 diffuse = vec3(0);
	vec3 specular  = vec3(0);

	vec3 L = normalize(light.position - worldPosition);
	float angle = dot(-L, light.direction);
	if (angle >= light.radius)
	{
		vec3 V = normalize(cameraPosition - worldPosition);
		vec3 R = reflect(-L, normal);

		float dotProductLN = max(dot(L, normal), 0.0f);
		float dotProductVR = max(dot(V, R), 0);

		float attenuation = calcAttenuation(light.position, worldPosition);

		ambient += (attenuation * vec3(0.5));
		diffuse += (attenuation * vec3(dotProductLN));
		specular += (attenuation * vec3(pow(dotProductVR, h)));
	}

	return vec3(texture(textureDiffuse, texCoord)) * ambient +
		vec3(texture(textureDiffuse, texCoord)) * diffuse +
		vec3(texture(textureSpecular, texCoord)) * specular;
}