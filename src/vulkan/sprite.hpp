#pragma once

#include "model.hpp"
#include "texture.hpp"

#include <memory>
#include <glm/glm.hpp>
#include <cstdint>

struct Sprite {
    std::shared_ptr<Model> model;
    Texture* texture;

    // glm::vec2 translation;
    // glm::vec2 scale;
    // glm::vec4 color;
    // glm::vec2 speed;

    // uint32_t textureIndex;
    // float rotation;
    uint32_t textureIndex;
};

struct alignas(16) SpriteData {
    glm::vec2 translation;
    glm::vec2 scale;
    glm::vec4 color;

    uint32_t textureIndex;
    float rotation;
};