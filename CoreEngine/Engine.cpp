#include "Engine.h"
#include "Graphics/VulkanContext.h"
#include "Scene/Scene.h"
#include "Renderer/Renderer.h"
#include "UI/EditorUI.h"
#include "Resource/ResourceManager.h"

namespace Kanae {

void Engine::initialize(const std::string& projectName) {
    vulkanContext = std::make_shared<VulkanContext>();
    vulkanContext->initialize(projectName);

    scene = std::make_shared<Scene>();
    renderer = std::make_shared<Renderer>();
    editorUI = std::make_shared<EditorUI>();
    resourceManager = std::make_shared<ResourceManager>();

    renderer->Initialize(vulkanContext);
    editorUI->Initialize(vulkanContext);
    resourceManager->Initialize();
}

void Engine::run() {
    while (!vulkanContext->shouldClose()) {
        vulkanContext->pollEvents();
        renderer->Render(*scene);
        editorUI->Render(*scene);
    }
}

void Engine::cleanup() {
    resourceManager->Cleanup();
    editorUI->Cleanup();
    renderer->Cleanup();
    vulkanContext->cleanup();
}

} // namespace Kanae 