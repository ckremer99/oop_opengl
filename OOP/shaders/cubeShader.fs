#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;  // This should be vec2 for texture coordinates
  
uniform vec3 viewPos;
uniform bool hasTexture;  // Use texture for diffuse
uniform bool hasSpecMap;  // Use texture for specular
uniform sampler2D diffuse_tex;  // Correct the sampler2D type
uniform sampler2D specMap;         // Specular map sampler
uniform Material material;
uniform Light lights[100];  // Correct the array declaration
uniform int numberOfLights;  // Number of active lights

void main()
{
    vec3 result = vec3(0.0);  // Initialize the final color to black

    // Loop through all lights
    for (int i = 0; i < numberOfLights; i++) {
        // Ambient lighting
        vec3 ambient = lights[i].ambient * (hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.ambient);
        
        // Diffuse lighting
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuseColor = hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.diffuse;
        vec3 diffuse = lights[i].diffuse * (diff * diffuseColor);
        
        // Specular lighting
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specularColor = hasSpecMap ? texture(specMap, TexCoords).rgb : material.specular;
        vec3 specular = lights[i].specular * (spec * specularColor);

        // Accumulate the result from all lights
        result += ambient + diffuse + specular;
    }

    FragColor = vec4(result, 1.0);
}
