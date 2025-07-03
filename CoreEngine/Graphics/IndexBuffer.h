#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

namespace Kanae {

class IndexBuffer {
public:
    IndexBuffer() = default;
    virtual ~IndexBuffer() = default;

    virtual void Create(const std::vector<uint32_t>& indices) = 0;
    virtual void Bind(VkCommandBuffer commandBuffer) = 0;
    virtual void Destroy() = 0;

protected:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
    size_t indexCount = 0;
};

} // namespace Kanae 