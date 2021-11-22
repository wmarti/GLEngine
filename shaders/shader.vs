#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor; // Specifcy a color output to the fragment shader
out vec4 vertexPosition;
uniform float offset;
void main() {
    gl_Position = vec4(aPos.x,-1.0*aPos.y + -offset, aPos.z, 1.0);
    vertexPosition = gl_Position;
    ourColor = aColor;
    //vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // dark-red
}