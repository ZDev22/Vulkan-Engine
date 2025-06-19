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

        std::cout << "Calling glfwInit()..." << std::endl;
        if (!glfwInit()) {
            std::cerr << "GLFW failed to initialize!" << std::endl;
            return -1;
        }
        std::cout << "GLFW initialized OK" << std::endl;
        if (!glfwVulkanSupported()) {
            std::cerr << "GLFW says Vulkan is NOT supported!" << std::endl;
            return -1;
        }
        std::cout << "GLFW says Vulkan is supported." << std::endl;

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