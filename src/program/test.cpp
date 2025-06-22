#include "program.hpp"
#include "sprite.hpp"
#include "global.hpp"

namespace vulkan {

    void program() {
        std::cout << "Starting sprite loading...\n";
        std::vector<std::string> texturePaths = { "logo.jpg" };
        sharedTexture = std::make_shared<Texture>(
            device,
            texturePaths[0],
            descriptorSetLayout,
            descriptorPool,
            *this
        );
        std::vector<Model::Vertex> vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
        };
        std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };
        auto sharedModel = std::make_shared<Model>(device, vertices, indices);

        Sprite sprite;
        sprite.model = sharedModel;
        sprite.texture = sharedTexture.get();

        for (int i = 0; i < 1; i++) {

            sprite.translation = glm::vec2(0.f, 0.f);

            sprite.scale = glm::vec2(.2f, .2f);
            sprite.rotation = 0.f;

            sprite.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            sprite.speed = { randomNumber(-.01f, .01f), randomNumber(-.01f, .01f) };
            sprite.textureIndex = 0;

            sprites.push_back(sprite);
        }
    }
}