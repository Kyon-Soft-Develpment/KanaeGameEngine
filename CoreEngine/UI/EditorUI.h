#pragma once

#include <memory>
#include <string>
#include <imgui.h>
#include "../Scene/Scene.h"
#include "../Graphics/VulkanContext.h"

namespace Kanae {

class EditorUI {
public:
    EditorUI() = default;
    virtual ~EditorUI() = default;

    virtual void Initialize(std::shared_ptr<VulkanContext> vulkanContext) = 0;
    virtual void Render(Scene& scene) = 0;
    virtual void Cleanup() = 0;

protected:
    std::shared_ptr<VulkanContext> vulkanContext;
    bool showDemoWindow = false;
    bool showSceneHierarchy = true;
    bool showInspector = true;
};

} // namespace Kanae 