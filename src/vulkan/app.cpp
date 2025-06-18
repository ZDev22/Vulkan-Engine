#include "app.hpp"
#include "sprite.hpp"
#include "global.hpp"

#include <iostream>
#include <stdexcept>
#include <chrono>

namespace vulkan {
    using clock = std::chrono::high_resolution_clock;
    static clock::time_point lastTime;
    static float deltaTime = 0.0f;
    static float fps = 0.0f;
    static float timeAccumulator = 0.0f;

    App::App() {
        pipeline = std::make_unique<Pipeline>(
            device,
            "vulkan/shaders/triangle.vert.spv",
            "vulkan/shaders/triangle.frag.spv",
            renderer.getSwapChainRenderPass()
        );
        pipeline->loadSprites(); // Populates vulkan::sprites
        global = std::make_unique<Global>(window);
        renderSystem = std::make_unique<RenderSystem>(
            device,
            window,
            renderer.getSwapChainRenderPass(),
            pipeline->getDescriptorSetLayout(),
            *global
        );
        renderSystem->initialize(); // Uses vulkan::sprites
    }

    App::~App() {}

    void App::run() {
        lastTime = clock::now();

        while (!window.shouldClose()) {
            auto currentTime = clock::now();
            std::chrono::duration<float> elapsed = currentTime - lastTime;
            deltaTime = elapsed.count();
            lastTime = currentTime;

            fps = 1.0f / deltaTime;
            timeAccumulator += deltaTime;

            if (timeAccumulator >= 1.0f) {
                std::cout << "FPS: " << fps << '\n';
                timeAccumulator = 0.0f;
            }

            glfwPollEvents();
            renderSystem->updateSprites(deltaTime);

            if (auto commandBuffer = renderer.beginFrame()) {
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderSystem->renderSprites(commandBuffer);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }
}