#include "light_manager.h"

LightManager::LightManager() { }

std::vector<Light> LightManager::lights;
int LightManager::numberOfLights = 0;

void LightManager::AddLight(Light light) {
    numberOfLights++;
    lights.push_back(light);
}

void LightManager::SetUniforms() {
    Shader shader = ResourceManager::GetShader("cubeShader");
    shader.SetInteger("numberOfLights", numberOfLights);
    for(int i = 0; i < numberOfLights; i++) {
        shader.SetVector3f(("lights[" + std::to_string(i) + "].position").c_str(), lights[i].position);
        shader.SetVector3f(("lights[" + std::to_string(i) + "].ambient").c_str(), lights[i].ambient);
        shader.SetVector3f(("lights[" + std::to_string(i) + "].diffuse").c_str(), lights[i].diffuse);
        shader.SetVector3f(("lights[" + std::to_string(i) + "].specular").c_str(), lights[i].specular);
    }
 
}
