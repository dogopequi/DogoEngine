#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Texture.h"
#define TWO_D_MAX_TEXTURES 16

#define MAX_QUADS 1000
#define MAX_LINES 1000

#define MAX_QUAD_VERTICES (MAX_QUADS * 4)
#define MAX_LINE_VERTICES (MAX_LINES * 2)

#define MAX_QUAD_INDICES (MAX_QUADS * 6)
#define MAX_LINE_INDICES (MAX_LINES * 2)
namespace Dogo
{
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texcoord;
		glm::vec3 normal;
		float texIndex;
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

	Quad CreateQuad(float x, float y, const glm::vec4& color, float scale, float texID);
	Line2D CreateLine2D(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
	class Renderer2D
	{
	public:
		virtual ~Renderer2D() = default;
		static Renderer2D* Create(const std::wstring& vertex, const std::wstring& pixel);
		virtual void SetViewMatrix(const glm::mat4& view) = 0;
		virtual void SetProjectionMatrix(const glm::mat4& proj) = 0;
		virtual void SetModelMatrix(const glm::mat4& model) = 0;
		virtual void SetTransformMatrix(const glm::mat4& model) = 0;
		virtual glm::mat4 GetViewMatrix() = 0;
		virtual glm::mat4 GetProjectionMatrix() = 0;
		virtual glm::mat4 GetModelMatrix() = 0;
		virtual glm::mat4 GetTransformMatrix() = 0;
		virtual void SetViewPos(const glm::vec3& pos) = 0;
		virtual void Submit(Quad& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(const Line2D& renderable) = 0;
		virtual void Flush() = 0;
	};
}