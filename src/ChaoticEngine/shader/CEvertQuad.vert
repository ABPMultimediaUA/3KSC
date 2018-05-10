#version 330 core
// Atributos
layout (location = 0) in vec3 VertexPosition;

// Salida para el fragment
out vec4 vertexColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(VertexPosition, 1.0f);
    vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
}