#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
// layout (location = 1) in vec2 aTexCoord;
layout (location = 3) in mat4 instanceMatrix;

// out vec3 ourColor; // Specifcy a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float offset;

void main() {
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
    // gl_Position = vec4(aPos, 1.0);
    // TexCoord = aTexCoord;
}