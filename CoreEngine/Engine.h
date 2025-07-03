#pragma once

#include <memory>
#include <string>
#include "Graphics/VulkanContext.h"
#include "Scene/Scene.h"
#include "Renderer/Renderer.h"
#include "UI/EditorUI.h"
#include "Resource/ResourceManager.h"

namespace Kanae {

class Engine {
public:
    Engine() = default;
    virtual ~Engine() = default;

    void initialize(const std::string& projectName);
    void run();
    void cleanup();

    std::shared_ptr<Scene> getScene() { return scene; }
    std::shared_ptr<ResourceManager> getResourceManager() { return resourceManager; }

private:
    std::shared_ptr<VulkanContext> vulkanContext;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<EditorUI> editorUI;
    std::shared_ptr<ResourceManager> resourceManager;
};

} // namespace Kanae 