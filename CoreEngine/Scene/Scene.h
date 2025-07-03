#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Math/Transform.h"
#include "Entity.h"
#include "Components/Component.h"
#include "Components/MeshComponent.h"
#include "Components/LightComponent.h"
#include "Components/CameraComponent.h"
#include "Components/ReflectionProbeComponent.h"

namespace Kanae {

class Scene {
public:
    Scene() = default;
    virtual ~Scene();

    std::shared_ptr<Entity> createEntity(const std::string& name);
    void deleteEntity(Entity* entity);
    
    Entity* getEntityByName(const std::string& name);
    Entity* getEntityById(uint64_t id);
    
    template<typename T>
    T* addComponent(Entity* entity);
    
    template<typename T>
    T* getComponent(Entity* entity);
    
    void update(float deltaTime);
    void render();
    
    // Scene management
    bool save(const std::string& path);
    bool load(const std::string& path);
    
    // Lighting and reflection
    void updateLighting();
    void updateReflectionProbes();
    void bakeGlobalIllumination();
    
    // Scene queries
    std::vector<LightComponent*> getLights() const;
    std::vector<ReflectionProbeComponent*> getReflectionProbes() const;
    CameraComponent* getActiveCamera() const;
    
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

private:
    std::string m_name;
    std::vector<std::shared_ptr<Entity>> entities;
    std::unordered_map<uint64_t, Entity*> m_entityMap;
    std::unordered_map<std::string, Entity*> m_entityNameMap;
    
    CameraComponent* m_activeCamera = nullptr;
    bool m_lightingDirty = true;
    bool m_reflectionsDirty = true;
};

} // namespace Kanae 