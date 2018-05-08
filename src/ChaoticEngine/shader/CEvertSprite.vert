#version 400 core
// Atributos
layout (location = 0) in vec4 Vertex;

// Salida para el fragment
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	TexCoords = Vertex.zw;
    gl_Position = projection * model * vec4(Vertex.xy, 0.0f, 1.0f);
}