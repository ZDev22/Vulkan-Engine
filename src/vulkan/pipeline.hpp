#pragma once

#include "device.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "global.hpp"

#include <vulkan/vulkan.h>

#include "../deps/c++/memory"
#include "../deps/c++/vector"
#include "../deps/c++/string"

class Pipeline {
public:
    Pipeline(Device& device, const std::string& vertFilepath, const std::string& fragFilepath, VkRenderPass renderPass);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void loadSprites();
    VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
    VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; } 
    VkDescriptorPool getDescriptorPool() const { return descriptorPool; }

private:
    static std::vector<char> readFile(const std::string& filepath);
    void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, VkRenderPass renderPass);
    VkShaderModule createShaderModule(const std::vector<char>& code);

    Device& device;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::shared_ptr<Texture> sharedTexture;
};