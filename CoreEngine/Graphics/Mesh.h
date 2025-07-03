#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Kanae {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct SubMesh {
    uint32_t indexCount = 0;
    uint32_t indexOffset = 0;
    uint32_t vertexOffset = 0;
    glm::mat4 transform = glm::mat4(1.0f);
};

public 
class Mesh {
public:
    Mesh() = default;
    virtual ~Mesh() = default;

    virtual void Create(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices) = 0;
    virtual void Bind(VkCommandBuffer commandBuffer) = 0;
    virtual void Draw(VkCommandBuffer commandBuffer) = 0;
    virtual void Destroy() = 0;

    bool loadFromFile(const std::string& filename);
    void setData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    
    const std::vector<SubMesh>& getSubMeshes() const { return m_subMeshes; }
    const glm::vec3& getBoundingBoxMin() const { return m_boundingBoxMin; }
    const glm::vec3& getBoundingBoxMax() const { return m_boundingBoxMax; }

protected:
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;
    size_t vertexCount = 0;
    size_t indexCount = 0;

    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    std::vector<SubMesh> m_subMeshes;

    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<IndexBuffer> m_indexBuffer;

    glm::vec3 m_boundingBoxMin;
    glm::vec3 m_boundingBoxMax;
};

} // namespace Kanae 