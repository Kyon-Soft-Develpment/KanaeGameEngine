#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Kanae {

class Transform {
public:
    Transform() = default;
    Transform(const glm::vec3& position, const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f));

    // Position
    const glm::vec3& getPosition() const { return m_position; }
    void setPosition(const glm::vec3& position);
    void translate(const glm::vec3& delta);

    // Rotation
    const glm::quat& getRotation() const { return m_rotation; }
    void setRotation(const glm::quat& rotation);
    void setRotation(const glm::vec3& eulerAngles);
    void rotate(const glm::quat& rotation);
    void rotate(const glm::vec3& eulerAngles);
    glm::vec3 getEulerAngles() const;

    // Scale
    const glm::vec3& getScale() const { return m_scale; }
    void setScale(const glm::vec3& scale);
    void scale(const glm::vec3& scale);

    // Directions
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    // Matrices
    const glm::mat4& getLocalMatrix();
    const glm::mat4& getWorldMatrix();
    void setParent(Transform* parent);
    Transform* getParent() const { return m_parent; }

    // Mark as dirty when transform changes
    void setDirty() { m_isDirty = true; }
    bool isDirty() const { return m_isDirty; }

private:
    void updateMatrices();

    glm::vec3 m_position = glm::vec3(0.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_localMatrix = glm::mat4(1.0f);
    glm::mat4 m_worldMatrix = glm::mat4(1.0f);
    
    Transform* m_parent = nullptr;
    bool m_isDirty = true;
};

} // namespace Kanae 