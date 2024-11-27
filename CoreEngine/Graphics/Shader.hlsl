cbuffer TransformConstants : register(b0) {
    matrix worldMatrix;
    matrix viewProjMatrix;
};

struct VSInput {
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

struct VSOutput {
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL;
};

VSOutput main(VSInput input) {
    VSOutput output;
    output.position = mul(viewProjMatrix, mul(worldMatrix, float4(input.position, 1.0)));
    output.texCoord = input.texCoord;
    output.normal = mul((float3x3)worldMatrix, input.normal); 
    return output;
}
Texture2D albedoMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState samplerState : register(s0);

cbuffer MaterialProperties : register(b1) {
    float smoothness;
};

cbuffer LightingConstants : register(b2) {
    float3 lightDirection; 
    float3 lightColor;
    float3 cameraPosition;
};

float4 main(VSOutput input) : SV_TARGET {

    float3 albedo = albedoMap.Sample(samplerState, input.texCoord).rgb;
    float3 normal = normalize(normalMap.Sample(samplerState, input.texCoord).rgb * 2.0 - 1.0);


    float3 worldPos = input.position.xyz; 
    float3 viewDir = normalize(cameraPosition - worldPos);
    float3 reflectDir = reflect(-lightDirection, normal);

    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specular = pow(max(dot(viewDir, reflectDir), 0.0), smoothness * 64);
    float3 color = (albedo * diffuse * lightColor) + (specular * lightColor);
    return float4(color, 1.0);
}

//Kyon Advanced Reality Shader 0.6 (KARS)
//By Maxim Lamas, KyonSoft 2024.

