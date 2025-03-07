
#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;
uniform float scale2;

out vec2 TexCoords;
out vec4 ParticleColor;

void main(){
    float scale = scale2;

    TexCoords = vertex.zw;
    ParticleColor = color;

    gl_Position = projection * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}