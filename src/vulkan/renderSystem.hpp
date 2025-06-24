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
    RenderSystem(Device& device, AppWindow& window, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout, Global& global);
    ~RenderSystem();

    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    void initialize();
    void renderSprites(VkCommandBuffer commandBuffer);
    void updateSprites();

private:
    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);
    void initializeSpriteData();
    void createTextureArrayDescriptorSet();

    Device& device;
    AppWindow& window;
    Global& global;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    std::unique_ptr<Buffer> spriteDataBuffer;
    VkDescriptorSet spriteDataDescriptorSet;
    VkDescriptorSet textureArrayDescriptorSet;
};