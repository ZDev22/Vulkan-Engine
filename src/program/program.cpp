#include "program.hpp"
#include "../main.hpp"
#include "../vulkan/global.hpp"

#include <glm/glm.hpp>

void tick() {
    for (auto& sprite : spriteData) {
        sprite._translation += sprite._speed * deltaTime;
        //sprite._scale += glm::vec2(randomNumber(-.005f, .005f), randomNumber(-.005f, .005f));
        //sprite._rotation += randomNumber(-.01f, .01f); 
    }
}