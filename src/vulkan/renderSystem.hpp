#pragma once

#include "device.hpp"
#include "pipeline.hpp"
#include "global.hpp"
#include "buffer.hpp"
#include "sprite.hpp" 

#include <memory>
#include <vector>

class RenderSystem {
public:
    RenderSystem(Device& device, Window& window, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout, Global& global);
    ~RenderSystem();

    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    void initialize();
    void renderSprites(VkCommandBuffer commandBuffer);
    void updateSprites(float deltaTime);

private:
    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);
    void initializeSpriteData();
    void createTextureArrayDescriptorSet();

    Device& device;
    Window& window;
    Global& global;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    std::unique_ptr<Buffer> spriteDataBuffer;
    VkDescriptorSet spriteDataDescriptorSet;
    VkDescriptorSet textureArrayDescriptorSet;
    std::vector<SpriteData> spriteData;
};