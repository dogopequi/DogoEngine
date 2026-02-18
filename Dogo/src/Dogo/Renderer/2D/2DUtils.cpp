#include "dgpch.h"
#include "2DUtils.h"
#include "Platform/OpenGL/GraphicsContext.h"
#include "Dogo/Utils/Logger.h"
namespace Dogo
{

	Circle GenerateCircle(glm::vec2 center, float radius, float tiling)
	{
		Circle c;
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		c.vertices[0] = {
			glm::vec3(center, 0.0f),
			color,
			glm::vec2(0.5f, 0.5f),
			0.0f, tiling
		};

		for (int i = 0; i <= RendererConstants::Circle_Segments; ++i)
		{
			float t = float(i) / float(RendererConstants::Circle_Segments);
			float angle = t * 2.0f * glm::pi<float>();
			float x = center.x + radius * glm::cos(angle);
			float y = center.y + radius * glm::sin(angle);

			float u = 0.5f + 0.5f * glm::cos(angle);
			float v = 0.5f - 0.5f * glm::sin(angle);

			c.vertices[i + 1] = {
				glm::vec3(x, y, 0.0f),
				color,
				glm::vec2(u, v),
				0.0f, tiling
			};
		}
		return c;
	
	}
	Quad CreateQuad(float x, float y, float width, float height, float pivotX, float pivotY, const UV& uv, float tiling)
	{
		Quad quad;
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		constexpr glm::vec2 texCoords[4] = { {0.0f, 0.0f}, {1.0f, 0.0f} , {1.0f, 1.0f} , {0.0f, 1.0f} };
		float left = x - pivotX;
		float bottom = y - pivotY;
		float right = left + width;
		float top = bottom + height;

		quad.vertices[0].position = { x,  y, 0.0f };
		quad.vertices[1].position = { x + width, y, 0.0f };
		quad.vertices[2].position = { x + width, y + height,    0.0f };
		quad.vertices[3].position = { x,  y + height,    0.0f };

		for (int i = 0; i < 4; ++i)
		{
			quad.vertices[i].color = color;
			quad.vertices[i].texcoord = texCoords[i];
			quad.vertices[i].texIndex = 0.0f;
			quad.vertices[i].tilingFactor = tiling;
		}

		return quad;
	}



	Line2D CreateLine2D(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color)
	{
		Line2D line;

		line.vertices[0].position = { start,0.0f };
		line.vertices[0].color = color;

		line.vertices[1].position = { end,0.0f };
		line.vertices[1].color = color;

		return line;
	}

	Triangle CreateTriangle(float origin, float scale, float tiling)
	{
		Triangle triangle;
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		float height = scale * glm::sqrt(3.0f) / 2.0f;

		glm::vec3 p0 = { origin,        0.0f, 0.0f };              
		glm::vec3 p1 = { origin + scale, 0.0f, 0.0f };             
		glm::vec3 p2 = { origin + scale / 2.0f, height, 0.0f };    

		glm::vec2 uv0 = { 0.0f, 1.0f };
		glm::vec2 uv1 = { 1.0f, 1.0f };
		glm::vec2 uv2 = { 0.5f, 0.0f };

		triangle.vertices[0] = { p0, color, uv0, 0.0f, tiling };
		triangle.vertices[1] = { p1, color, uv1, 0.0f, tiling };
		triangle.vertices[2] = { p2, color, uv2, 0.0f, tiling };
		return triangle;
	}


	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, float tiling)
	{
		ThickLine quad;
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		glm::vec2 dir = glm::normalize(p1 - p0);
		glm::vec2 normal = glm::vec2(-dir.y, dir.x);
		glm::vec2 offset = normal * (thickness * 0.5f);

		quad.vertices[0].position = glm::vec3(p0 + offset, 0.0f);
		quad.vertices[1].position = glm::vec3(p1 + offset, 0.0f);
		quad.vertices[2].position = glm::vec3(p1 - offset, 0.0f);
		quad.vertices[3].position = glm::vec3(p0 - offset, 0.0f);

		for (int i = 0; i < 4; i++) {
			quad.vertices[i].color = color;
			quad.vertices[i].texcoord = glm::vec2(0.0f, 1.0f);
			quad.vertices[i].texIndex = 0.0f;
			quad.vertices[i].tilingFactor = tiling;
		}

		return quad;
	}

}