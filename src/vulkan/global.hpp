#pragma once

#include "sprite.hpp"
#include "window.hpp"

#include <glm/glm.hpp>

struct Push {
    glm::mat4 projection;
};

extern std::vector<Sprite> sprites;

class Global {
public:
    Global(Window& window) : window(window), aspectRatio(1.0f) {
        setAspectRatio(); 
    }

    void setAspectRatio() {
        extent = window.getExtent();
        aspectRatio = static_cast<float>(extent.width) / extent.height;
    }

    float getAspectRatio() const { return aspectRatio; }

private:
    VkExtent2D extent;
    float aspectRatio;
    Window& window;
};