#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0f);  // Combine lightColor (vec3) with 1.0f to make vec4
}
