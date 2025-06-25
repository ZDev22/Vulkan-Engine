#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "../../deps/glfw/GLFW/glfw3.h"
#include <unordered_map>
#include <vector>

#include "../../vulkan/window.hpp"

class Keyboard {
public:
    Keyboard(AppWindow& appWindow);

    bool keyPressed(int key);
    bool keyHit(int key);

private:
    GLFWwindow* window;
    std::unordered_map<int, int> keyIndexMap;
    std::vector<int> glfwKeys;
    unsigned char keys[113] = {0};
};

#endif