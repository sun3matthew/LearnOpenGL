// #ifndef CONTEXTFREE_H
// #define CONTEXTFREE_H


// #include <vector>
// #include <string>

// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>

// struct Entity{
//     glm::vec3 position;
//     glm::vec3 rotation;
//     float scale;
// };

// struct Rules{
//     int value; // probability of this rule
//     std::string rule;
// };


// class ContextFree
// {
//     public:
        // ContextFree(std::string axiom, std::vector<Rules> rules);
//     private:
//         std::vector<Rules> rules;
//         std::string axiom;
//         std::vector<Entity> run();
// };

// #endif

#include <ContextFree.h>
#include <queue>

#include <iostream>

ContextFree::ContextFree() {}

float random(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

std::vector<Entity> ContextFree::run(){

    srand(time(NULL));


    std::vector<Entity> entities;

    std::queue<Entity> queue;
    queue.push({glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.5f, 1.5f), 1.0f});

    entities.push_back(queue.front());

    std::vector<int> ruleValues = {50, 1, 1};

    int sum = 0;
    for(int i = 0; i < ruleValues.size(); i++){
        sum += ruleValues[i];
    }

    while(!queue.empty()){
        Entity entity = queue.front();
        queue.pop();


        if (entity.scale < 0.01f){
            continue;
        }

        glm::vec3 direction = glm::vec3(glm::cos(entity.rotation.x) * glm::sin(entity.rotation.y), glm::sin(entity.rotation.x), glm::cos(entity.rotation.x) * glm::cos(entity.rotation.y));
        glm::vec3 position = entity.position + direction * entity.scale;

        entities.push_back({position, entity.rotation, entity.scale});

        float r = random(0.0f, 1.0f);
        for (int i = 0; i < ruleValues.size(); i++){
            if(r < (float) ruleValues[i] / sum){
                queue.push({position, glm::vec2(entity.rotation.x + random(-0.1f, 0.1f), entity.rotation.y + random(-0.1f, 0.1f)), entity.scale * 0.99f});
                if(i == 1){
                    queue.push({position, glm::vec2(entity.rotation.x + random(0.2, 0.4), entity.rotation.y + random(-3.0f, 3.0f)), entity.scale * 0.8f});
                }else if(i == 2){
                    queue.push({position, glm::vec2(entity.rotation.x - random(0.2, 0.4), entity.rotation.y + random(-3.0f, 3.0f)), entity.scale * 0.8f});
                }
                break;
            }
            r -= (float) ruleValues[i] / sum;
        }
    }

    return entities;
}
