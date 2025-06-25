#include "program.hpp"
#include "../main.hpp"
#include "../vulkan/global.hpp"

#include <glm/glm.hpp>

#include <iostream>
#include <string>

void tick() {
    for (size_t d = 0; d < sprites.size(); d++) {
        sprites[d].translation += sprites[d].speed * deltaTime;
        //sprite._scale += glm::vec2(randomNumber(-.005f, .005f), randomNumber(-.005f, .005f));
        //sprite._rotation += randomNumber(-.01f, .01f); 
    }
}