#version 330 core
out vec4 FragColor;
in vec3 outputColor;

uniform vec3 ourColor;

void main(){
    FragColor = vec4(ourColor, 1.0) + vec4(outputColor, 1.0);
}