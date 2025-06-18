#include "main.hpp"

#include "vulkan/app.hpp"
#include "vulkan/compileShader.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <random>

short scene = 1;

uint32_t state = 123456789;
float normalized;

uint32_t xorshift32() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

float randomNumber(float min, float max) {
    normalized = xorshift32() / static_cast<float>(UINT32_MAX);
    return min + (max - min) * normalized;
}

int main() {
    if (compile()) {
        vulkan::App app{};

        try {
            app.run();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    else { return 0; }
}