#include "light_manager.h"

LightManager::LightManager() { }

std::vector<Light> LightManager::lights;

void LightManager::AddLight(Light light) {
    lights.push_back(light);
}

void LightManager::SetUniforms() {
    Shader shader = ResourceManager::GetShader("cubeShader");
    shader.SetVector3f("light.position", lights[0].position);
    shader.SetVector3f("light.ambient", lights[0].ambient);
    shader.SetVector3f("light.diffuse", lights[0].diffuse);
    shader.SetVector3f("light.specular", lights[0].specular);
}
