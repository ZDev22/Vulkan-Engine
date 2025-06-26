#include "renderSystem.hpp"
#include "global.hpp"
#include "../program/program.hpp"

#include <stdexcept>
#include <iostream>
#include <array>
#include <algorithm>
#include <execution>

#include <glm/gtc/matrix_transform.hpp>

const uint32_t batchSize = 100;
uint32_t instanceCount;

using namespace std;

RenderSystem::RenderSystem(Device& device, AppWindow& window, Keyboard& keyboard, Program& program, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout, Global& global)
    : device(device), window(window), global(global), keyboard(keyboard), program(program), descriptorSetLayout(descriptorSetLayout) {
    createPipelineLayout();
    createPipeline(renderPass);
    cout << "RenderSystem created" << endl;
}

RenderSystem::~RenderSystem() {
    if (spriteDataBuffer) {
        spriteDataBuffer->unmap();
    }
}

void RenderSystem::initialize() {
    initializeSpriteData();
    createTextureArrayDescriptorSet();
}

void RenderSystem::createPipelineLayout() {
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(Push);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw runtime_error("failed to create pipeline layout!");
    }
}

void RenderSystem::createPipeline(VkRenderPass renderPass) {
    pipeline = make_unique<Pipeline>(
        device,
        "vulkan/shaders/triangle.vert.spv",
        "vulkan/shaders/triangle.frag.spv",
        renderPass
    );
}

void RenderSystem::initializeSpriteData() {

    VkDeviceSize bufferSize = sizeof(SpriteData) * sprites.size();
    spriteDataBuffer = make_unique<Buffer>(
        device,
        bufferSize,
        1,
        VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        device.properties.limits.minStorageBufferOffsetAlignment
    );

    spriteDataBuffer->map();
    spriteDataBuffer->writeToBuffer(sprites.data(), bufferSize);
}

void RenderSystem::createTextureArrayDescriptorSet() {
    if (!spriteDataBuffer) {
        throw runtime_error("spriteDataBuffer is not initialized!");
    }

    textureArrayDescriptorSet = spriteCPU[0].texture->getDescriptorSet();
    if (textureArrayDescriptorSet == VK_NULL_HANDLE) {
        throw runtime_error("Failed to get valid texture descriptor set");
    }
    cout << "Using texture array descriptor set: " << textureArrayDescriptorSet << endl;

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = pipeline->getDescriptorPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &descriptorSetLayout;

    if (vkAllocateDescriptorSets(device.device(), &allocInfo, &spriteDataDescriptorSet) != VK_SUCCESS) {
        throw runtime_error("failed to allocate descriptor set!");
    }

    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = spriteDataBuffer->getBuffer();
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(SpriteData) * (sprites.size() + spriteCPU.size());

    VkWriteDescriptorSet bufferWrite{};
    bufferWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    bufferWrite.dstSet = spriteDataDescriptorSet;
    bufferWrite.dstBinding = 0;
    bufferWrite.dstArrayElement = 0;
    bufferWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    bufferWrite.descriptorCount = 1;
    bufferWrite.pBufferInfo = &bufferInfo;

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = spriteCPU[0].texture->getImageView();
    imageInfo.sampler = spriteCPU[0].texture->getSampler();

    VkWriteDescriptorSet imageWrite{};
    imageWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    imageWrite.dstSet = spriteDataDescriptorSet;
    imageWrite.dstBinding = 1;
    imageWrite.dstArrayElement = 0;
    imageWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    imageWrite.descriptorCount = spriteCPU[0].texture->getIsArray() ? spriteCPU[0].texture->getArrayLayers() : 1;
    imageWrite.pImageInfo = &imageInfo;

    array<VkWriteDescriptorSet, 2> descriptorWrites = {bufferWrite, imageWrite};
    vkUpdateDescriptorSets(device.device(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);

    cout << "Combined descriptor set created: " << spriteDataDescriptorSet << endl;
}

void RenderSystem::renderSprites(VkCommandBuffer commandBuffer) {
    if (sprites.empty() || !spriteCPU[0].model) {
        cerr << "No valid sprites or model to render" << endl;
        return;
    }

    global.setAspectRatio();
    pipeline->bind(commandBuffer);
    auto model = spriteCPU[0].model;
    model->bind(commandBuffer);
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipelineLayout(), 0, 1, &spriteDataDescriptorSet, 0, nullptr);

    Push push{};
    
    push.projection = glm::ortho(
        -1.0f, 1.0f,  
        -1.0f, 1.0f,  
        -1.0f, 1.0f   
    );

    vkCmdPushConstants(commandBuffer, pipeline->getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(Push), &push);

    uint32_t spriteCount = static_cast<uint32_t>(sprites.size());
    for (uint32_t i = 0; i < spriteCount; i += batchSize) {
        instanceCount = min(batchSize, spriteCount - i);
        model->draw(commandBuffer, instanceCount);
    }
}

void RenderSystem::updateSprites() {

    program.tick();

    VkDeviceSize bufferSize = sizeof(SpriteData) * sprites.size();
    spriteDataBuffer->writeToBuffer(sprites.data(), bufferSize);
}