#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Mesh.h"

namespace Kanae {

class ResourceManager {
public:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    virtual void Initialize() = 0;
    virtual void Cleanup() = 0;

    virtual std::shared_ptr<Shader> LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) = 0;
    virtual std::shared_ptr<Texture> LoadTexture(const std::string& name, const std::string& path) = 0;
    virtual std::shared_ptr<Mesh> LoadMesh(const std::string& name, const std::string& path) = 0;

    virtual std::shared_ptr<Shader> GetShader(const std::string& name) = 0;
    virtual std::shared_ptr<Texture> GetTexture(const std::string& name) = 0;
    virtual std::shared_ptr<Mesh> GetMesh(const std::string& name) = 0;

    // Primitive mesh creation functions
    virtual std::shared_ptr<Mesh> createPlaneMesh(float width, float height) = 0;
    virtual std::shared_ptr<Mesh> createCubeMesh(float size) = 0;
    virtual std::shared_ptr<Mesh> createSphereMesh(float radius, uint32_t segments, uint32_t rings) = 0;
    virtual std::shared_ptr<Mesh> createCylinderMesh(float radius, float height, uint32_t segments) = 0;
    virtual std::shared_ptr<Mesh> createConeMesh(float radius, float height, uint32_t segments) = 0;

protected:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
};

} // namespace Kanae 