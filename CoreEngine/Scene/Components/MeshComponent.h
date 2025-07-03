#pragma once

#include "Component.h"
#include "../../Graphics/Mesh.h"
#include "../../Graphics/Material.h"

namespace Kanae {

class MeshComponent : public Component {
public:
    explicit MeshComponent(Entity* owner);
    ~MeshComponent() override;

    void initialize() override;
    void update(float deltaTime) override;
    void render() override;

    void setMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
    void setMaterial(std::shared_ptr<Material> material) { m_material = material; }

    Mesh* getMesh() const { return m_mesh.get(); }
    Material* getMaterial() const { return m_material.get(); }

    bool castShadows() const { return m_castShadows; }
    void setCastShadows(bool cast) { m_castShadows = cast; }

    bool receiveShadows() const { return m_receiveShadows; }
    void setReceiveShadows(bool receive) { m_receiveShadows = receive; }

    const char* getTypeName() const override { return "MeshComponent"; }

private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
    bool m_castShadows = true;
    bool m_receiveShadows = true;
};

} // namespace Kanae 