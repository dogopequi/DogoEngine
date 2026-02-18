#pragma once
#include "Dogo/Core.h"
#include "Dogo/Utils/Logger.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/Texture2D.h"
#include "Platform/OpenGL/Shader.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "Dogo/Systems/Assets/Assets.h"
#include "UV.h"

namespace Dogo
{
	namespace RendererConstants
	{
		static constexpr const size_t Circle_Segments = 32;
		static constexpr const size_t Circle_Vertices = Circle_Segments + 2;
		static constexpr const size_t Circle_Indices = Circle_Segments * 3;
		static constexpr const size_t Max_Characters = 100;
		static constexpr const size_t MaxTextures = 16;
	}
	struct Batch {
		uint32_t startIndex;
		uint32_t indexCount;
	};
	struct Rect
	{
		glm::vec2 pos;
		float width;
		float height;
	};
	struct Viewport
	{
		glm::vec2 pos;
		glm::vec2 size;
		glm::vec3 color;
		glm::vec2 framebufferSize;
		bool transparent;
		bool visible = false;
	};

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texcoord;
		float texIndex;
		float tilingFactor;
	};

	struct LineVertex {
		glm::vec3 position;
		glm::vec4 color;
	};
	struct Quad {
		Vertex vertices[4];
	};
	struct Line2D {
		LineVertex vertices[2];
	};
	struct Triangle {
		Vertex vertices[3];
	};
	struct Circle {
		Vertex vertices[RendererConstants::Circle_Segments + 2];
	};
	struct ThickLine {
		Vertex vertices[4];
	};

	struct Character {
		glm::vec2 uvTopLeft;
		glm::vec2 uvBottomRight;
		glm::ivec2 size;
		glm::ivec2 bearing;
		uint32_t advance;
	};

	struct TextCommand {
		std::string text;
		float x, y;
		float scale;
		glm::vec3 color;
		glm::mat4 transform;
	};

	Circle GenerateCircle(glm::vec2 center, float radius, float tiling = 1.0f);
	Quad CreateQuad(float x, float y, float width, float height, float pivotX, float pivotY, const UV& uv = UV(), float tiling = 1.0f);
	Line2D CreateLine2D(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
	Triangle CreateTriangle(float origin, float scale, float tiling = 1.0f);
	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, float tiling = 1.0f);
}