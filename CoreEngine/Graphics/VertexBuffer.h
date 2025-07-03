#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace Kanae {

class VertexBuffer {
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;

    virtual void Create(const std::vector<glm::vec3>& vertices) = 0;
    virtual void Bind(VkCommandBuffer commandBuffer) = 0;
    virtual void Destroy() = 0;

protected:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
    size_t vertexCount = 0;
};

} // namespace Kanae 