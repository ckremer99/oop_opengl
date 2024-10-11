#include "light_manager.h"

LightManager::LightManager() { }

std::vector<Light> LightManager::lights;
int LightManager::numberOfLights = 0;

float LightManager::constant = 1.0f;
float LightManager::linear = 0.09f;
float LightManager::quadratic = 0.052f;

glm::vec3 LightManager::dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
glm::vec3 LightManager::dirLightAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
glm::vec3 LightManager::dirLightDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
glm::vec3 LightManager::dirLightSpecular = glm::vec3(0.5f, 0.5f, 0.5f);

void LightManager::AddLight(Light light) {
    numberOfLights++;
    lights.push_back(light);
}

void LightManager::SetUniforms() {
    Shader shader = ResourceManager::GetShader("cubeShader");
    
    shader.SetVector3f("dirLight.direction", dirLightDirection);
    shader.SetVector3f("dirLight.ambient", dirLightAmbient);
    shader.SetVector3f("dirLight.diffuse", dirLightDiffuse);
    shader.SetVector3f("dirLight.specular", dirLightSpecular);
    
    shader.SetInteger("numberOfpointLights", numberOfLights);
    for(int i = 0; i < numberOfLights; i++) {
        shader.SetVector3f(("pointLights[" + std::to_string(i) + "].position").c_str(), lights[i].position);
        shader.SetVector3f(("pointLights[" + std::to_string(i) + "].ambient").c_str(), lights[i].ambient);
        shader.SetVector3f(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), lights[i].diffuse);
        shader.SetVector3f(("pointLights[" + std::to_string(i) + "].specular").c_str(), lights[i].specular);
        shader.SetFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), constant);
        shader.SetFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), linear);
        shader.SetFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), quadratic);

    }
 
}
