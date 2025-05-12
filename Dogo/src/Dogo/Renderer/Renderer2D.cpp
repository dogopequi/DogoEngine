#include "dgpch.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLRenderer2D.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Logger.h"
namespace Dogo
{
	Renderer2D* Renderer2D::Create(const std::wstring& vertex, const std::wstring& pixel)
	{
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				return new OpenGLRenderer2D(vertex, pixel);
				break;
			case Dogo::RenderAPI::VULKAN:
				DG_FATAL("Not Implemented");
				break;
			default:
				DG_FATAL("No API specified");
				break;
			}
		}
		return nullptr;
	}
	Quad CreateQuad(float x, float y, const glm::vec4& color, float scale, float texID)
	{
		Quad quad;
		quad.vertices[0].position = { x, y, 0.0f };
		quad.vertices[1].position = { x + scale, y, 0.0f };
		quad.vertices[2].position = { x + scale, y + scale, 0.0f };
		quad.vertices[3].position = { x, y + scale, 0.0f };
		quad.vertices[0].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[1].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[2].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[3].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[0].texcoord = { 0.0f, 0.0f };
		quad.vertices[1].texcoord = { 1.0f, 0.0f };
		quad.vertices[2].texcoord = { 1.0f, 1.0f };
		quad.vertices[3].texcoord = { 0.0f, 1.0f };
		quad.vertices[0].color = { color.x, color.y, color.z, color.w };
		quad.vertices[1].color = { color.x, color.y, color.z, color.w };
		quad.vertices[2].color = { color.x, color.y, color.z, color.w };
		quad.vertices[3].color = { color.x, color.y, color.z, color.w };
		quad.vertices[0].texIndex = texID;
		quad.vertices[1].texIndex = texID;
		quad.vertices[2].texIndex = texID;
		quad.vertices[3].texIndex = texID;
		return quad;
	}
}