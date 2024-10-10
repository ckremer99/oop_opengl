#include <vector>
#include "resource_manager.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Light {
    glm::vec3 position;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class LightManager {
public:
    LightManager();
    static std::vector<Light> lights;
    static void AddLight(Light light);
    static void SetUniforms();
    
    static float ambientStrength;
    
};
