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
    
    static glm::vec3 dirLightDirection;
    static glm::vec3 dirLightAmbient;
    static glm::vec3 dirLightDiffuse;
    static glm::vec3 dirLightSpecular; 
    
    static std::vector<Light> lights;
    static int numberOfLights;
    static void AddLight(Light light);
    static void SetUniforms();
    
    static float constant;
    static float linear;
    static float quadratic;
    
    static float ambientStrength;
    
};
