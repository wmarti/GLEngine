#version 330 core
/*
If you declare a uniform that isn't used anywhere in your GLSL code,
the compiler will silently remove the variable from the compiled version 
which is the cause for several frustrating errors; keep this in mind!
*/


//in vec4 vertexColor;
in vec4 vertexPosition;
in vec2 TexCoord;
out vec4 FragColor;

// uniform sampler2DArray atlas;
// uniform sampler2D tex;
uniform sampler2DArray textureArray;
int layer = 1;

void main() {
    FragColor = texture(textureArray, vec3(TexCoord, 241));
}