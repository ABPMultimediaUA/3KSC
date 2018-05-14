
#version 330 core

//Estructura para guardar la textura. Se guardan las propiedades difusas y especulares de la textura
struct TMaterial{
	sampler2D texture_diffuse;
	sampler2D texture_specular;

	float Shininess;
};

//Estructura para guardar las luces: Posicion y propiedades; ambiental, difusa y especular
#define NR_POINT_LIGHTS 5
struct PointLight{
	vec3 Position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

//Estado de OpenGL: textura y luz de los tipos anteriores
uniform vec3 		viewPos;
uniform TMaterial 	Material;
uniform PointLight 	Light[NR_POINT_LIGHTS];

//Entrada desde el vertex shader
in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;  

out vec4 FragColor;

//Functions
vec3 calcPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir);

void main(){
	vec3 norm 	 = normalize(Normal);
	vec3 viewDir = normalize(viewPos - Position);

	vec3 result;

	for(int i = 0; i < NR_POINT_LIGHTS; i++){
		result += calcPointLight(Light[i], norm, Position, viewDir);
	}

	FragColor = vec4(result, 1.0f);
}

// calculates the color when using a point light.
vec3 calcPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir){
    vec3 lightDir = normalize(light.Position - position);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
    
    // attenuation
    float distance = length(light.Position - position);
    
    //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    float attenuation = 1.0f;
    // combine results
    vec3 ambient = light.Ambient * vec3(texture(Material.texture_diffuse, TexCoords));
    
    vec3 diffuse = light.Diffuse * diff * vec3(texture(Material.texture_diffuse, TexCoords));
    
    vec3 specular = light.Specular * spec * vec3(texture(Material.texture_specular, TexCoords));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}
