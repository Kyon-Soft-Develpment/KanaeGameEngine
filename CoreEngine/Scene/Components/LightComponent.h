#pragma once

#include <glm/glm.hpp>
#include "Component.h"

namespace Kanae {

enum class LightType {
    Directional,
    Point,
    Spot
};

class LightComponent : public Component {
public:
    LightComponent() = default;
    virtual ~LightComponent() = default;

    void setType(LightType type) { lightType = type; }
    void setColor(const glm::vec3& color) { lightColor = color; }
    void setIntensity(float intensity) { lightIntensity = intensity; }
    void setRange(float range) { lightRange = range; }
    void setSpotAngle(float angle) { spotAngle = angle; }

    LightType getType() const { return lightType; }
    const glm::vec3& getColor() const { return lightColor; }
    float getIntensity() const { return lightIntensity; }
    float getRange() const { return lightRange; }
    float getSpotAngle() const { return spotAngle; }

private:
    LightType lightType = LightType::Point;
    glm::vec3 lightColor = glm::vec3(1.0f);
    float lightIntensity = 1.0f;
    float lightRange = 10.0f;
    float spotAngle = 45.0f;
};

} // namespace Kanae 