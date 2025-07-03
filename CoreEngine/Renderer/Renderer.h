#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include "../Scene/Scene.h"
#include "../Graphics/VulkanContext.h"

namespace Kanae {

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer() = default;

    virtual void Initialize(std::shared_ptr<VulkanContext> vulkanContext) = 0;
    virtual void Render(const Scene& scene) = 0;
    virtual void Cleanup() = 0;

protected:
    std::shared_ptr<VulkanContext> vulkanContext;
    std::vector<VkCommandBuffer> commandBuffers;
};

} // namespace Kanae 