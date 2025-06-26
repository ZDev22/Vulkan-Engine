#pragma once

#include "device.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "global.hpp"

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <string>

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
    void setTexture(const std::vector<std::string>& texturePaths);

    Device& device;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::unique_ptr<Texture> spriteTexture;
    std::vector<std::string> texturePaths;
};