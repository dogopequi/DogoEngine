Texture2D gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
};


float4 main(PS_INPUT input) : SV_Target
{
    return float4(input.color, 1.0f);
    //return gTexture.Sample(gSampler, input.texcoord);
}