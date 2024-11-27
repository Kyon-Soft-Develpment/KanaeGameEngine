#pragma once
#include <d3d12.h>
#include <wrl.h>

struct Vertex {
    float position[3];
    float color[4];
};

class GraphicsDevice {
public:
    void CreateVertexBuffer(ID3D12Device* device, ID3D12Resource*& vertexBuffer, D3D12_VERTEX_BUFFER_VIEW& vertexBufferView);
};
