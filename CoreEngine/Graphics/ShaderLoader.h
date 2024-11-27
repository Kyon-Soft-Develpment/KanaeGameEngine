#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>

class ShaderLoader {
public:
    static ID3DBlob* CompileShader(const std::wstring& filename, const std::string& entryPoint, const std::string& target);
};
