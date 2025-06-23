#pragma once

#include "window.hpp"
#include "device.hpp"
#include "renderer.hpp"
#include "pipeline.hpp"
#include "renderSystem.hpp"
#include "global.hpp" 

#include <memory>

class App {
public:
    App();
    ~App();

    App(const App&) = delete;
    App& operator=(const App&) = delete;

    void run();

private:
    Window window{1280, 720, "Vulkan"};
    Device device{window};
    Renderer renderer{window, device};
    std::unique_ptr<Pipeline> pipeline;
    std::unique_ptr<Global> global; 
    std::unique_ptr<RenderSystem> renderSystem;
};