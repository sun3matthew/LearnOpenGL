#ifndef CONTEXTFREE_H
#define CONTEXTFREE_H


#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Entity{
    glm::vec3 position;
    glm::vec2 rotation;
    float scale;
};

class ContextFree
{
    public:
        ContextFree();
        std::vector<Entity> run();
};

#endif