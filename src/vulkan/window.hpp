#pragma once

#include <string>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int w, int h, std::string name);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); }
    VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
    bool wasWindowResized() { return framebufferResized; }
    void resetWindowResizedFlag() { framebufferResized = false; }
    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
    void waitEvents() { glfwWaitEvents(); }

private:
    void initWindow();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    int width;
    int height;
    bool framebufferResized = false;
    std::string windowName;
    GLFWwindow* window;
};