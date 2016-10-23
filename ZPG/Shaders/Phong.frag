#version 330 core
in vec3 ourColor;
in vec3 worldPosition;
in vec3 worldNormal;

out vec4 color;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	// Intenzita paprsku L
	const float I_L = 1;

	// Intenzita okolniho svetla
	const float I_A = 1;
	// Koeficient odrazu okolniho svetla
	const float R_A = 0.3;

	// Koeficient zrcadloveho odrazu
	const float R_S = 10;
	// Ostrost zrcadloveho odrazu
	const float h = 20;

	vec3 L = normalize(lightPosition - worldPosition);
	vec3 R = reflect(-L, worldNormal);
	vec3 V = normalize(cameraPosition - worldPosition);

	float dotProductLN = max(dot(L, worldNormal), 0.0f);
	float dotProductVR = max(dot(V, R), 0);

	vec3 diffuse = I_L * ourColor * vec3(dotProductLN);
	vec3 ambient =  I_A * R_A * ourColor;
	vec3 specular = I_L * R_S * vec3(pow(dotProductVR, h));

	//color = vec4(diffuse, 1.0);
	//color = vec4(ambient, 1.0);
	//color = vec4(specular, 1.0);
	color = vec4(diffuse + ambient + specular, 1.0);
	//color = vec4(ourColor, 1);
};