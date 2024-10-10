#include "cube.h"

Cube::Cube(glm::vec3 position, glm::vec3 color, bool isLight) {
    this->camera = ResourceManager::GetCamera("camera");
}

void Cube::Draw() {
    glm::mat4 projection = glm::perspective(glm::radians(this->camera.Zoom), (float)(800.0f / 600.0f), 0.1f, 100.0f);
    glm::mat4 view = this->camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
   

    Shader shader = ResourceManager::GetShader("shader");
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
