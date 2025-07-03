#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

namespace Kanae {

class Material {
public:
    Material();
    ~Material();

    void setShader(std::shared_ptr<Shader> shader) { m_shader = shader; }
    Shader* getShader() const { return m_shader.get(); }

    void bind();
    void unbind();

    // Textures
    void setTexture(const std::string& name, std::shared_ptr<Texture> texture);
    Texture* getTexture(const std::string& name) const;

    // Material properties
    void setFloat(const std::string& name, float value);
    void setVector2(const std::string& name, const glm::vec2& value);
    void setVector3(const std::string& name, const glm::vec3& value);
    void setVector4(const std::string& name, const glm::vec4& value);
    void setMatrix4(const std::string& name, const glm::mat4& value);

    float getFloat(const std::string& name) const;
    glm::vec2 getVector2(const std::string& name) const;
    glm::vec3 getVector3(const std::string& name) const;
    glm::vec4 getVector4(const std::string& name) const;
    glm::mat4 getMatrix4(const std::string& name) const;

    // PBR properties
    void setAlbedo(const glm::vec3& albedo) { m_albedo = albedo; }
    void setMetallic(float metallic) { m_metallic = metallic; }
    void setRoughness(float roughness) { m_roughness = roughness; }
    void setAO(float ao) { m_ao = ao; }
    void setEmissive(const glm::vec3& emissive) { m_emissive = emissive; }

    const glm::vec3& getAlbedo() const { return m_albedo; }
    float getMetallic() const { return m_metallic; }
    float getRoughness() const { return m_roughness; }
    float getAO() const { return m_ao; }
    const glm::vec3& getEmissive() const { return m_emissive; }

private:
    std::shared_ptr<Shader> m_shader;
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
    
    // Material properties
    std::unordered_map<std::string, float> m_floatValues;
    std::unordered_map<std::string, glm::vec2> m_vector2Values;
    std::unordered_map<std::string, glm::vec3> m_vector3Values;
    std::unordered_map<std::string, glm::vec4> m_vector4Values;
    std::unordered_map<std::string, glm::mat4> m_matrix4Values;

    // PBR properties
    glm::vec3 m_albedo = glm::vec3(1.0f);
    float m_metallic = 0.0f;
    float m_roughness = 0.5f;
    float m_ao = 1.0f;
    glm::vec3 m_emissive = glm::vec3(0.0f);
};

} // namespace Kanae 