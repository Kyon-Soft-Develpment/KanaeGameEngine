#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

namespace Kanae {

class CubeMap;

class ReflectionProbeComponent : public Component {
public:
    ReflectionProbeComponent() = default;
    virtual ~ReflectionProbeComponent() = default;

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;

    // Probe properties
    void setResolution(uint32_t res) { resolution = res; }
    void setRange(float range) { m_range = range; }
    void setBoxProjection(bool enabled) { m_useBoxProjection = enabled; }
    void setBoxSize(const glm::vec3& size) { boxSize = size; }
    void setBoxOffset(const glm::vec3& offset) { boxOffset = offset; }
    void setBlendDistance(float distance) { m_blendDistance = distance; }
    void setImportance(int importance) { m_importance = importance; }

    uint32_t getResolution() const { return resolution; }
    float getRange() const { return m_range; }
    bool useBoxProjection() const { return m_useBoxProjection; }
    const glm::vec3& getBoxSize() const { return boxSize; }
    const glm::vec3& getBoxOffset() const { return boxOffset; }
    float getBlendDistance() const { return m_blendDistance; }
    int getImportance() const { return m_importance; }

    // Reflection data
    CubeMap* getCubeMap() const { return m_cubeMap.get(); }
    bool isDirty() const { return m_isDirty; }
    void markDirty() { m_isDirty = true; }

    // Capture and update methods
    void captureReflections();
    void updateReflections();
    void blendWithNeighbors(const std::vector<ReflectionProbeComponent*>& neighbors);

    const char* getTypeName() const override { return "ReflectionProbeComponent"; }

private:
    void createCubeMap();
    void renderCubemapFace(int face);

    std::unique_ptr<CubeMap> m_cubeMap;
    uint32_t resolution = 256;
    float m_range = 10.0f;
    bool m_useBoxProjection = false;
    glm::vec3 boxSize = glm::vec3(10.0f);
    glm::vec3 boxOffset = glm::vec3(0.0f);
    float m_blendDistance = 1.0f;
    int m_importance = 0;
    bool m_isDirty = true;

    // Rendering resources
    unsigned int m_captureFBO = 0;
    unsigned int m_captureRBO = 0;
};

} // namespace Kanae 