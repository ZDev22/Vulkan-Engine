#pragma once

#include "model.hpp"
#include "texture.hpp"

#include <glm/glm.hpp>

struct Sprite {
    std::shared_ptr<Model> model;
    Texture* texture;

    uint32_t textureIndex;
};

struct alignas(16) SpriteData {
    glm::vec2 translation;
    glm::vec2 scale;
    glm::vec4 color;

    uint32_t textureIndex;
    float rotation;
};