#include "ShaderLoader.h"
#include "GraphicsDevice.h"
#include <d3d12.h>
#include <stdexcept>


ID3D12Device* InitializeDevice();
void CreatePipelineState(ID3DBlob* vertexShader, ID3DBlob* pixelShader, ID3D12Device* device, ID3D12PipelineState** pipelineState);
void RenderFrame(D3D12_VERTEX_BUFFER_VIEW& vertexBufferView, ID3D12PipelineState* pipelineState);

int main() {
    try {

        ID3D12Device* device = InitializeDevice();
        if (!device) {
            throw std::runtime_error("Failed to initialize device.");
        }


        ID3DBlob* vertexShader = ShaderLoader::CompileShader(L"Shaders/vertex_shader.hlsl", "main", "vs_5_0");
        ID3DBlob* pixelShader = ShaderLoader::CompileShader(L"Shaders/pixel_shader.hlsl", "main", "ps_5_0");


        GraphicsDevice graphicsDevice;
        ID3D12Resource* vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
        graphicsDevice.CreateVertexBuffer(device, vertexBuffer, vertexBufferView);


        ID3D12PipelineState* pipelineState = nullptr;
        CreatePipelineState(vertexShader, pixelShader, device, &pipelineState);

        RenderFrame(vertexBufferView, pipelineState);

        if (vertexBuffer) vertexBuffer->Release();
        if (pipelineState) pipelineState->Release();
        if (device) device->Release();
    }
    catch (const std::exception& e) {

        OutputDebugStringA(e.what());
        return -1;
    }

    return 0;
}
