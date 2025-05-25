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
	Circle GenerateCircle(glm::vec2 center, float radius, glm::vec4 color, float texID)
	{
		Circle c;
		glm::vec3 normal = { 0.0f, 0.0f, 1.0f };

		c.vertices[0] = {
			glm::vec3(center, 0.0f),
			color,
			glm::vec2(0.5f, 0.5f),
			normal,
			texID
		};

		for (int i = 0; i <= CIRCLE_SEGMENTS; ++i)
		{
			float t = float(i) / float(CIRCLE_SEGMENTS);
			float angle = t * 2.0f * glm::pi<float>();
			float x = center.x + radius * glm::cos(angle);
			float y = center.y + radius * glm::sin(angle);

			float u = 0.5f + 0.5f * glm::cos(angle);
			float v = 0.5f + 0.5f * glm::sin(angle);

			c.vertices[i + 1] = {
				glm::vec3(x, y, 0.0f),
				color,
				glm::vec2(u, v),
				normal,
				texID
			};
		}
		return c;
	
	}
	Quad CreateQuad(float x, float y, const glm::vec4& color, float width, float height, float texID)
	{
		Quad quad;
		quad.vertices[0].position = { x, y, 0.0f };
		quad.vertices[1].position = { x + width, y, 0.0f };
		quad.vertices[2].position = { x + width, y + height, 0.0f };
		quad.vertices[3].position = { x, y + height, 0.0f };

		// Set the normal vector for each vertex (assuming a flat 2D quad)
		quad.vertices[0].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[1].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[2].normal = { 0.0f, 0.0f, 1.0f };
		quad.vertices[3].normal = { 0.0f, 0.0f, 1.0f };

		// Set texture coordinates for each vertex (assuming a basic texture mapping)
		quad.vertices[0].texcoord = { 0.0f, 0.0f };
		quad.vertices[1].texcoord = { 1.0f, 0.0f };
		quad.vertices[2].texcoord = { 1.0f, 1.0f };
		quad.vertices[3].texcoord = { 0.0f, 1.0f };

		// Apply the color to each vertex
		quad.vertices[0].color = { color.x, color.y, color.z, color.w };
		quad.vertices[1].color = { color.x, color.y, color.z, color.w };
		quad.vertices[2].color = { color.x, color.y, color.z, color.w };
		quad.vertices[3].color = { color.x, color.y, color.z, color.w };

		// Apply texture index to each vertex
		quad.vertices[0].texIndex = texID;
		quad.vertices[1].texIndex = texID;
		quad.vertices[2].texIndex = texID;
		quad.vertices[3].texIndex = texID;

		return quad;
	}

	Line2D CreateLine2D(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
	{
		Line2D line;

		line.vertices[0].position = start;
		line.vertices[0].color = color;

		line.vertices[1].position = end;
		line.vertices[1].color = color;

		return line;
	}

	Triangle CreateTriangle(float origin, const glm::vec4& color, float scale, float texID)
	{
		Triangle triangle;
		float height = scale * glm::sqrt(3.0f) / 2.0f;

		glm::vec3 p0 = { origin,        0.0f, 0.0f };              
		glm::vec3 p1 = { origin + scale, 0.0f, 0.0f };             
		glm::vec3 p2 = { origin + scale / 2.0f, height, 0.0f };    

		glm::vec2 uv0 = { 0.0f, 0.0f };
		glm::vec2 uv1 = { 1.0f, 0.0f };
		glm::vec2 uv2 = { 0.5f, 1.0f };

		glm::vec3 normal = { 0.0f, 0.0f, 1.0f };

		triangle.vertices[0] = { p0, color, uv0, normal, texID };
		triangle.vertices[1] = { p1, color, uv1, normal, texID };
		triangle.vertices[2] = { p2, color, uv2, normal, texID };
		return triangle;
	}
	RoundedRect CreateRoundedRect(glm::vec2 center, glm::vec2 size, float radius, glm::vec4 color, float texID) {
		static const float sina[ROUNDED_RECT_VERTICES] = {
				 0.0f,  0.1736482f,  0.3420201f,  0.5f,        0.6427876f,  0.7660444f,
				 0.8660254f,  0.9396926f,  0.9848077f,  1.0f,        0.9848077f,  0.9396926f,
				 0.8660254f,  0.7660444f,  0.6427876f,  0.5f,        0.3420201f,  0.1736482f,
				 0.0f, -0.1736482f, -0.3420201f, -0.5f,       -0.6427876f, -0.7660444f,
				-0.8660254f, -0.9396926f, -0.9848077f, -1.0f,       -0.9848077f, -0.9396926f,
				-0.8660254f, -0.7660444f, -0.6427876f, -0.5f,       -0.3420201f, -0.1736482f
		};
		static const float* cosa = sina + ROUNDED_RECT_SEGMENTS;

		RoundedRect rr;
		glm::vec2 half = size * 0.5f;
		radius = std::min(radius, std::min(half.x, half.y));
		glm::vec2 d = half - glm::vec2(radius);
		glm::vec3 normal{ 0.0f, 0.0f, 1.0f };

		int idx = 0;
		rr.vertices[idx++] = { glm::vec3(center, 0.0f), color, glm::vec2(0.0f), normal, texID };

		for (int i = 0; i < ROUNDED_RECT_SEGMENTS * 4; ++i) {
			glm::vec2 off;
			if (i < ROUNDED_RECT_SEGMENTS)       off = { +d.x, +d.y };
			else if (i < ROUNDED_RECT_SEGMENTS * 2)   off = { -d.x, +d.y };
			else if (i < ROUNDED_RECT_SEGMENTS * 3)   off = { -d.x, -d.y };
			else                                       off = { +d.x, -d.y };

			float s = sina[i];
			float c = cosa[i];
			glm::vec2 p = center + off + glm::vec2(c, s) * radius;

			rr.vertices[idx++] = { glm::vec3(p, 0.0f), color, glm::vec2(0.0f), normal, texID };
		}

		return rr;
	}



	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color, float texIndex)
	{
		ThickLine quad;

		glm::vec2 dir = glm::normalize(p1 - p0);
		glm::vec2 normal = glm::vec2(-dir.y, dir.x);
		glm::vec2 offset = normal * (thickness * 0.5f);

		quad.vertices[0].position = glm::vec3(p0 + offset, 0.0f);
		quad.vertices[1].position = glm::vec3(p1 + offset, 0.0f);
		quad.vertices[2].position = glm::vec3(p1 - offset, 0.0f);
		quad.vertices[3].position = glm::vec3(p0 - offset, 0.0f);

		for (int i = 0; i < 4; i++) {
			quad.vertices[i].color = color;
			quad.vertices[i].texcoord = glm::vec2(0.0f);
			quad.vertices[i].texIndex = texIndex;
			quad.vertices[i].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		return quad;
	}

	void Renderer2D::Push(const glm::mat4& mat, boolean override)
	{
		if(override)
			m_TransformStack.push_back(mat);
		else
			m_TransformStack.push_back(mat * m_TransformStack.back());
		m_TransformBack = &m_TransformStack.back();
	}

	void Renderer2D::Pop()
	{
		if (m_TransformStack.size() > 1)
		{
			m_TransformStack.pop_back();
		}
		m_TransformBack = &m_TransformStack.back();
	}

	glm::mat4 Renderer2D::GetTransformBack()
	{
		return *m_TransformBack;
	}

}