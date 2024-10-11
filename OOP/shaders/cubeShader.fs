#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos; 
uniform bool hasTexture;
uniform bool hasSpecMap;
uniform sampler2D diffuse_tex;
uniform sampler2D specMap;
uniform Material material;
uniform PointLight pointLights[100];
uniform DirLight dirLight;
uniform int numberOfpointLights;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = normalize(Normal);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);  // Corrected the argument list
    
    for (int i = 0; i < numberOfpointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // Ambient color
    vec3 ambient = light.ambient * (hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.ambient);
    
    // Diffuse color
    vec3 diffuse = light.diffuse * diff * (hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.diffuse);
    
    // Specular color
    vec3 specular = light.specular * spec * (hasSpecMap ? texture(specMap, TexCoords).rgb : material.specular);
    
    // Apply attenuation to all components
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Ambient color
    vec3 ambient = light.ambient * (hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.ambient);
    
    // Diffuse color
    vec3 diffuse = light.diffuse * diff * (hasTexture ? texture(diffuse_tex, TexCoords).rgb : material.diffuse);
    
    // Specular color
    vec3 specular = light.specular * spec * (hasSpecMap ? texture(specMap, TexCoords).rgb : material.specular);
    
    return (ambient + diffuse + specular);
}
