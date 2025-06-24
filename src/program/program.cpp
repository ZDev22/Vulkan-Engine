#include "program.hpp"
#include "../main.hpp"
#include "../vulkan/global.hpp"

#include "../deps/glm/glm/glm.h"

void tick() {
    for (auto& sprite : spriteData) {
        sprite._translation += sprite._speed * deltaTime;
        sprite._scale += vec2(randomNumber(-.1f, .1f), randomNumber(-.1f, .1f));
    }
}