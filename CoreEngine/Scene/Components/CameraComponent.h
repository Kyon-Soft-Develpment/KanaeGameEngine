#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

namespace Kanae {

enum class ProjectionType {
    Perspective,
    Orthographic
};

class CameraComponent : public Component {
public:
    CameraComponent() = default;
    virtual ~CameraComponent() = default;

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;

    void setFOV(float fov) { fieldOfView = fov; updateProjection(); }
    void setNearPlane(float near) { nearPlane = near; updateProjection(); }
    void setFarPlane(float far) { farPlane = far; updateProjection(); }
    void setAspectRatio(float ratio) { aspectRatio = ratio; updateProjection(); }
    void setOrthographicSize(float size) { m_orthographicSize = size; updateProjection(); }
    void setProjectionType(ProjectionType type) { m_projectionType = type; updateProjection(); }

    float getFOV() const { return fieldOfView; }
    float getNearPlane() const { return nearPlane; }
    float getFarPlane() const { return farPlane; }
    float getAspectRatio() const { return aspectRatio; }
    float getOrthographicSize() const { return m_orthographicSize; }
    ProjectionType getProjectionType() const { return m_projectionType; }

    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
    const glm::mat4& getViewMatrix() const { return viewMatrix; }
    glm::mat4 getViewProjectionMatrix() const { return projectionMatrix * viewMatrix; }

    bool isInFrustum(const glm::vec3& point) const;
    bool isInFrustum(const glm::vec3& center, float radius) const;
    bool isInFrustum(const glm::vec3& min, const glm::vec3& max) const;

    glm::vec3 screenToWorldPoint(const glm::vec2& screenPos, float depth = 0.0f) const;
    glm::vec3 screenToWorldDirection(const glm::vec2& screenPos) const;

    const char* getTypeName() const override { return "CameraComponent"; }

protected:
    void updateProjection() {
        projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
    }

    void updateView() {
        if (auto transform = getEntity()->getTransform()) {
            const auto& position = transform->getPosition();
            const auto& rotation = transform->getRotation();
            viewMatrix = glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

private:
    float fieldOfView = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    float aspectRatio = 16.0f / 9.0f;
    float m_orthographicSize = 5.0f;

    ProjectionType m_projectionType = ProjectionType::Perspective;

    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    // Frustum planes
    glm::vec4 m_frustumPlanes[6];
};

} // namespace Kanae 