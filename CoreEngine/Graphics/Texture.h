#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <memory>

namespace Kanae {

class Texture {
public:
    Texture() = default;
    virtual ~Texture() = default;

    virtual void Create(const std::string& texturePath) = 0;
    virtual void Bind(VkCommandBuffer commandBuffer) = 0;
    virtual void Destroy() = 0;

protected:
    VkImage image = VK_NULL_HANDLE;
    VkDeviceMemory imageMemory = VK_NULL_HANDLE;
    VkImageView imageView = VK_NULL_HANDLE;
    VkSampler sampler = VK_NULL_HANDLE;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t mipLevels = 1;
};

} // namespace Kanae 