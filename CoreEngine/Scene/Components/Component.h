#pragma once

namespace Kanae {

class Entity;

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void initialize() {}
    virtual void update(float deltaTime) {}
    virtual void cleanup() {}

    Entity* getEntity() const { return entity; }
    void setEntity(Entity* e) { entity = e; }

    virtual const char* getTypeName() const = 0;

protected:
    Entity* entity = nullptr;
};

} // namespace Kanae 