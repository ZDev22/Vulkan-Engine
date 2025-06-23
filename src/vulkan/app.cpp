#include "app.hpp"
#include "sprite.hpp"
#include "global.hpp"

#include "../deps/c++/iostream"
#include "../deps/c++/stdexcept"
#include "../deps/c++/chrono"

using HighResClock = std::chrono::high_resolution_clock;
static HighResClock::time_point lastTime;
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
    pipeline->loadSprites();
    global = std::make_unique<Global>(window);
    renderSystem = std::make_unique<RenderSystem>(
        device,
        window,
        renderer.getSwapChainRenderPass(),
        pipeline->getDescriptorSetLayout(),
        *global
    );
    renderSystem->initialize();
}

App::~App() {}

void App::run() {
    lastTime = HighResClock::now();

    while (!window.shouldClose()) {
        auto currentTime = HighResClock::now();
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