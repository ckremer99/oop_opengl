#include "cube.h"

Cube::Cube(glm::vec3 position, glm::vec3 color, bool isLight) {
    this->position = position;
    this->color = color;
    this->isLight = isLight;
    
    this->shader = isLight ? ResourceManager::GetShader("lightShader") : ResourceManager::GetShader("cubeShader");
    
    if (isLight) {
        Light light;
        light.position = this->position;
        light.ambient = glm::vec3(1.0f) * this->color;
        light.diffuse = glm::vec3(0.8f) * this->color;
        light.specular = glm::vec3(1.0f) * glm::vec3(1.0f);
        LightManager::AddLight(light);
    } else {
        material.ambient = glm::vec3(0.1) * this->color;
        material.diffuse = glm::vec3(0.5) * this->color;
        material.specular = glm::vec3(0.5) * glm::vec3(1.0f);
        material.shininess = 32.0f;
    }
    
    
}

void Cube::InitCube(unsigned int &VAO) {
    unsigned int VBO; 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 
}

void Cube::SetTexture(std::string name) {
    hasTexture = true;
    texture = ResourceManager::GetTexture(name);
}

void Cube::SetScale(float value) {
    this->scale = value;
}

void Cube::Draw() {
    // Get the camera and compute matrices
    Camera& camera = ResourceManager::GetCamera(cameraName);
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)(800.0f / 600.0f), 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    model = glm::translate(model, this->position);
    
    Shader shader;
    
    if (isLight) {
        // Use the light shader for light sources
        shader = ResourceManager::GetShader("lightShader");
        shader.Use();
        
        // Set the light color (light sources are typically just displayed as bright objects)
        shader.SetVector3f("lightColor", this->color[0], this->color[1], this->color[2]);
        glm::vec3 viewPos = ResourceManager::GetCamera("camera").Position;
        shader.SetVector3f("viewPos", viewPos);
        
        // Set transformation matrices
        shader.SetMatrix4("model", model);
        shader.SetMatrix4("projection", projection);
        shader.SetMatrix4("view", view);

    } else {
        // Use the cube shader for normal cubes
        shader = ResourceManager::GetShader("cubeShader");
        shader.Use();
        // Set material
        shader.SetVector3f("material.ambient", material.ambient);
        shader.SetVector3f("material.diffuse", material.diffuse);
        shader.SetVector3f("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
        shader.SetFloat("material.shininess", material.shininess);
        shader.SetVector3f("viewPos", ResourceManager::GetCamera("camera").Position);
        
        // Set object color
        shader.SetVector3f("objectColor", this->color[0], this->color[1], this->color[2]);
        
        // Set light and material properties via LightManager
        LightManager::SetUniforms();  // Set light uniforms like light position, color, etc.

        // Handle textures
        if (hasTexture) {
            texture.Bind();
            shader.SetInteger("hasTexture", 1);  // Enable texture
        } else {
            shader.SetInteger("hasTexture", 0);  // No texture
        }

        // Set transformation matrices
        shader.SetMatrix4("model", model);
        shader.SetMatrix4("projection", projection);
        shader.SetMatrix4("view", view);
    }

    // Draw the object (whether cube or light)
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
