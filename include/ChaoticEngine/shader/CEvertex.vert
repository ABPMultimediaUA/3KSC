#version 400 core
// Atributos
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 TextureCoords;

// Salida para el fragment

out vec3 Position; 
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
    Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0f));
    Normal = normalize(NormalMatrix * VertexNormal);
    TexCoords = TextureCoords;

    gl_Position = MVP * vec4(VertexPosition, 1.0f);
}