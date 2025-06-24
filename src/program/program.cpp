#include "program.hpp"
#include "../vulkan/global.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <execution>

void tick() {
    std::for_each(std::execution::par, spriteData.begin(), spriteData.end(), [](auto& sprite) {
        sprite._translation += sprite._speed * deltaTime;
    });
}