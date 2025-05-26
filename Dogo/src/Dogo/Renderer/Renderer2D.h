#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Texture.h"
#include "Dogo/Renderer/Shader.h"
#define TWO_D_MAX_TEXTURES 16

#define MAX_QUADS 1000
#define MAX_LINES 1000
#define MAX_TRIANGLES 1000
#define MAX_CIRCLES 1000
#define MAX_ROUNDED_RECTS 1000
#define MAX_THICK_LINES 1000
#define MAX_CHARACTERS 100

#define CIRCLE_SEGMENTS 32

#define ROUNDED_RECT_SEGMENTS 9
#define ROUNDED_RECT_VERTICES (1 + ROUNDED_RECT_SEGMENTS*4)

#define MAX_QUAD_VERTICES (MAX_QUADS * 4)
#define MAX_LINE_VERTICES (MAX_LINES * 2)
#define MAX_TRIANGLE_VERTICES (MAX_TRIANGLES * 3)
#define MAX_CIRCLE_VERTICES (MAX_CIRCLES * (CIRCLE_SEGMENTS + 2))
#define MAX_ROUNDED_RECT_VERTICES (MAX_ROUNDED_RECTS * ROUNDED_RECT_VERTICES)
#define MAX_THICK_LINES_VERTICES (MAX_THICK_LINES * 4)

#define MAX_QUAD_INDICES (MAX_QUADS * 6)
#define MAX_LINE_INDICES (MAX_LINES * 2)
#define MAX_TRIANGLE_INDICES (MAX_TRIANGLES * 3)
#define MAX_CIRCLE_INDICES (MAX_CIRCLES * 3 * CIRCLE_SEGMENTS)
#define MAX_ROUNDED_RECT_INDICES  (MAX_ROUNDED_RECTS * ROUNDED_RECT_SEGMENTS * 4 * 3)
#define MAX_THICK_LINES_INDICES (MAX_THICK_LINES * 6)

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
	struct Triangle {
		Vertex vertices[3];
	};
	struct Circle {
		Vertex vertices[CIRCLE_SEGMENTS + 2];
	};
	struct RoundedRect {
		Vertex vertices[ROUNDED_RECT_VERTICES];
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

	Circle GenerateCircle(glm::vec2 center, float radius, glm::vec4 color, float texID);
	Quad CreateQuad(float x, float y, const glm::vec4& color, float width, float height, float texID);
	Line2D CreateLine2D(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
	Triangle CreateTriangle(float origin, const glm::vec4& color, float scale, float texID);
	RoundedRect CreateRoundedRect(glm::vec2 center, glm::vec2 size, float radius, glm::vec4 color, float texID);
	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color, float texIndex);
	
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
		virtual glm::mat4 GetTransformBack();
		virtual void SetViewPos(const glm::vec3& pos) = 0;
		virtual void Submit(Quad& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(Triangle& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(Circle& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(RoundedRect& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(ThickLine& renderable, Texture* tex = nullptr) = 0;
		virtual void Submit(Line2D& renderable) = 0;
		virtual void SubmitText(const std::string& text, float x, float y, float scale, const glm::vec3& color = glm::vec3(1.0f)) = 0;
		virtual void Flush() = 0;
		virtual void Push(const glm::mat4& mat, boolean override = false);
		virtual void Pop();
		virtual void LoadFont(const std::string& fontPath, uint32_t size) = 0;
		virtual float ComputeTextWidth(const std::string& text, float scale) = 0;
		virtual void RenderText() = 0;
		virtual float GetFontHeight(float scale) = 0;
		virtual Shader* ExposeShader() const = 0;
		virtual void SetShader(Shader* shader) = 0;
		virtual void DrawFrameBuffer(Quad& quad) = 0;
		//inline static void SetInstance(Renderer2D* instance) { m_Instance = instance; }
		//inline static Renderer2D* GetInstance() { return m_Instance; }

	protected:
		Renderer2D() { m_TransformStack.push_back(glm::mat4(1.0f));
		m_TransformBack = &m_TransformStack.back();
		}

		std::vector<glm::mat4> m_TransformStack;
		const glm::mat4* m_TransformBack;

	//private:
	//	inline static Renderer2D* m_Instance;
	};
}