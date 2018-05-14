
#version 330

struct TMaterial{
	float Shininess;
};

layout(location = 0) out vec4 out_color;

uniform sampler2D colorTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform TMaterial 	Material;

uniform int texture_diffuse;
uniform int texture_specular;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

const vec3	ambinet = vec3(0.90, 0.0, 0.20);
const int	levels = 5;
const float scaleFactor = 1.0 / levels;

void main(){
	vec3 color= texture(colorTexture, TexCoords).rgb;

	vec3 Kd = vec3(0.30,0.80,0.10);
	
	vec3 L = normalize(lightPos - Position);
	vec3 V = normalize(viewPos - Position);

	float difuza = max(0, dot(L,Normal));
	Kd = Kd * texture_diffuse* floor(difuza * levels) * scaleFactor;

	vec3 H = normalize(L + V);

	float speculara = 0;

	if(dot(L,Normal) > 0.0){
        speculara = texture_specular * pow( max(0, dot( H, Normal)), Material.Shininess);
	}	
	
	float specMask = (pow(dot(H, Normal), Material.Shininess) > 0.4) ? 1 : 0;
	float edgeMask;
	
	if(dot(V, Normal) >= 1)
		edgeMask = 1;
	else if(dot(V, Normal) > 0.75)
		edgeMask = 0.75;
	else if(dot(V, Normal) > 0.50)
		edgeMask = 0.50;
	else if(dot(V, Normal) > 0.25)
		edgeMask = 0.25;
	else
		edgeMask = 0.25;


	//float edgeMask = (dot(V, Normal) >  0.2) ? 1 : 0;
	
	color = edgeMask * (color + Kd + speculara * specMask);

	out_color = vec4(color,1);
}