#include "Engine.h"
#include "Scene/Components/MeshComponent.h"
#include "Scene/Components/LightComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/ReflectionProbeComponent.h"
#include "Resource/ResourceManager.h"

using namespace Kanae;

int main() {
    // Initialize engine
    Engine& engine = Engine::getInstance();
    if (!engine.initialize("Examples/BasicScene")) {
        return 1;
    }

    // Get current scene
    Scene* scene = engine.getCurrentScene();

    // Create main camera
    Entity* cameraEntity = scene->createEntity("MainCamera");
    auto* camera = cameraEntity->addComponent<CameraComponent>();
    camera->setFOV(60.0f);
    camera->setNearPlane(0.1f);
    camera->setFarPlane(1000.0f);
    cameraEntity->getTransform().setPosition(glm::vec3(0.0f, 2.0f, -5.0f));
    cameraEntity->getTransform().setRotation(glm::vec3(15.0f, 0.0f, 0.0f));

    // Create directional light
    Entity* sunLight = scene->createEntity("Sun");
    auto* light = sunLight->addComponent<LightComponent>();
    light->setType(LightType::Directional);
    light->setColor(glm::vec3(1.0f, 0.95f, 0.8f));
    light->setIntensity(2.0f);
    sunLight->getTransform().setRotation(glm::vec3(45.0f, -45.0f, 0.0f));

    // Create reflection probe
    Entity* probeEntity = scene->createEntity("ReflectionProbe");
    auto* probe = probeEntity->addComponent<ReflectionProbeComponent>();
    probe->setResolution(256);
    probe->setRange(20.0f);
    probeEntity->getTransform().setPosition(glm::vec3(0.0f, 2.0f, 0.0f));

    // Create floor
    Entity* floor = scene->createEntity("Floor");
    auto* floorMesh = floor->addComponent<MeshComponent>();
    floorMesh->setMesh(engine.getResourceManager()->createPlaneMesh(10.0f, 10.0f));
    auto floorMaterial = std::make_shared<Material>();
    floorMaterial->setAlbedo(glm::vec3(0.5f, 0.5f, 0.5f));
    floorMaterial->setMetallic(0.0f);
    floorMaterial->setRoughness(0.8f);
    floorMesh->setMaterial(floorMaterial);

    // Create sphere
    Entity* sphere = scene->createEntity("Sphere");
    auto* sphereMesh = sphere->addComponent<MeshComponent>();
    sphereMesh->setMesh(engine.getResourceManager()->createSphereMesh(1.0f, 32, 32));
    auto sphereMaterial = std::make_shared<Material>();
    sphereMaterial->setAlbedo(glm::vec3(1.0f, 0.2f, 0.2f));
    sphereMaterial->setMetallic(1.0f);
    sphereMaterial->setRoughness(0.2f);
    sphereMesh->setMaterial(sphereMaterial);
    sphere->getTransform().setPosition(glm::vec3(0.0f, 1.0f, 0.0f));

    // Run engine
    engine.run();

    return 0;
} 