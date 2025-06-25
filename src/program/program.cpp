#include "program.hpp"
#include "../main.hpp"
#include "../vulkan/global.hpp"

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include "functions/keyboard.hpp"

float speedY;

Program::Program(Keyboard& keyboard)
: keyboard(keyboard) {
    // Currently no initialization to be seen
}

void Program::tick() {
    speedY -= .1f;
    sprites[0].translation.y += speedY * deltaTime;
    sprites[0].rotation -= .1f;
    if (keyboard.keyPressed(GLFW_KEY_A)) {
        std::cout << "true\n";
    } 
}