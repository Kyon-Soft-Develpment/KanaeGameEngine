#include "Scene.h"

namespace Kanae {

Scene::~Scene() {
    entities.clear();
}

std::shared_ptr<Entity> Scene::createEntity(const std::string& name) {
    auto entity = std::make_shared<Entity>(name);
    entities.push_back(entity);
    return entity;
}

} // namespace Kanae 