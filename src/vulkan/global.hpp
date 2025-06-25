#pragma once

#include "sprite.hpp"
#include "window.hpp"

#include <glm/glm.hpp>

struct Push {
    glm::mat4 projection;
};

extern std::vector<SpriteData> sprites;
<<<<<<< HEAD
extern std::vector<Sprite> spriteCPU;
=======
>>>>>>> 8f63bf24a961c161c2b42e28ba25a93dc3536ad3

extern float deltaTime;

class Global {
public:
    Global(AppWindow& window) : window(window), aspectRatio(1.0f) {
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
    AppWindow& window;
};