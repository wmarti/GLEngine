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

uniform sampler2D ourTexture;

void main() {
    // FragColor = texture(ourTexture, TexCoord);
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}