#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;    // Light color (vec3)


void main()
{
    FragColor = vec4(lightColor, 1.0f);
}
