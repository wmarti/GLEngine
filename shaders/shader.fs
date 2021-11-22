#version 330 core
/*
If you declare a uniform that isn't used anywhere in your GLSL code,
the compiler will silently remove the variable from the compiled version 
which is the cause for several frustrating errors; keep this in mind!
*/

//in vec4 vertexColor;
in vec4 vertexPosition;
out vec4 FragColor;

uniform vec4 ourColor; // we set this in the OpenGL code

void main() {
    FragColor = vertexPosition;
}