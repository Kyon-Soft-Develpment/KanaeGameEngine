#include "ShaderLoader.h"
#include <d3dcompiler.h>
#include <stdexcept>
#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>

class ShaderLoader {
public:
    static ID3DBlob* CompileShader(const std::wstring& filename, const std::string& entryPoint, const std::string& target);
};


ID3DBlob* ShaderLoader::CompileShader(const std::wstring& filename, const std::string& entryPoint, const std::string& target) {
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    HRESULT hr = D3DCompileFromFile(
        filename.c_str(), nullptr, nullptr, entryPoint.c_str(),
        target.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0,
        &shaderBlob, &errorBlob);

    if (FAILED(hr)) {
        if (errorBlob) {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        throw std::runtime_error("Failed to compile shader");
    }

    return shaderBlob;
}
