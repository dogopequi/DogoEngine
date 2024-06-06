//cbuffer MatrixBuffer : register(b0)
//{
//    matrix model;
//    matrix view;
//    matrix projection;
//    matrix MVP;
//};
cbuffer MatrixBuffer : register(b0)
{
    matrix model;
};
cbuffer MatrixBuffer : register(b1)
{
    matrix view;
};
cbuffer MatrixBuffer : register(b2)
{
    matrix projection;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
};


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    float4 worldPosition = float4(input.position, 1.0f);
    worldPosition = mul(model, worldPosition);
    worldPosition = mul(view, worldPosition);
    worldPosition = mul(projection, worldPosition);
    
    //worldPosition = mul(MVP, worldPosition);
    output.position = worldPosition;
    output.color = input.color;
    output.texcoord = input.texcoord;
    return output;
}