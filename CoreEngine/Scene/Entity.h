#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Components/Component.h"
#include "Components/Transform.h"

namespace Kanae {

class Entity {
public:
    Entity(const std::string& name = "Entity") : name(name) {
        transform = addComponent<Transform>();
    }
    virtual ~Entity() = default;

    template<typename T>
    T* addComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        auto component = std::make_shared<T>();
        components[std::type_index(typeid(T))] = component;
        return component.get();
    }

    template<typename T>
    T* getComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    const std::string& getName() const { return name; }
    Transform* getTransform() { return transform; }

private:
    std::string name;
    Transform* transform;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};

} // namespace Kanae 