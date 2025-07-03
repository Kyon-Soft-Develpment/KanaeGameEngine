#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <memory>

namespace Kanae {

class Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;

    virtual void Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) = 0;
    virtual void Bind(VkCommandBuffer commandBuffer) = 0;
    virtual void Destroy() = 0;

protected:
    VkShaderModule vertexShaderModule = VK_NULL_HANDLE;
    VkShaderModule fragmentShaderModule = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline pipeline = VK_NULL_HANDLE;
};

} // namespace Kanae 