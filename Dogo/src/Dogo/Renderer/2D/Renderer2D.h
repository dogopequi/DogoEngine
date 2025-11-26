#pragma once
#include "Dogo/Core.h"
#include "Dogo/Utils/Logger.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Core/Texture.h"
#include "Dogo/Renderer/Core/Shader.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "Dogo/Systems/AssetSystem.h"

#define MAX_CHARACTERS 100

#define CIRCLE_SEGMENTS 32
#define CIRCLE_VERTICES CIRCLE_SEGMENTS + 2
#define MAX_CIRCLE_VERTICES (MAX_CIRCLES * (CIRCLE_VERTICES))
#define CIRCLE_INDICES 3 * CIRCLE_SEGMENTS

#define MAX_CIRCLE_INDICES (MAX_CIRCLES * CIRCLE_INDICES)


namespace Dogo
{

	struct UV
	{
		glm::vec2 uvMin;
		glm::vec2 uvMax;
		UV() : uvMin(0.0f, 0.0f), uvMax(1.0f, 1.0f) {}
		UV(const glm::vec2& min, const glm::vec2& max) : uvMin(min), uvMax(max) {}
		UV(float xMin, float yMin, float xMax, float yMax): uvMin(xMin, yMin), uvMax(xMax, yMax) {}
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

	Circle GenerateCircle(glm::vec2 center, float radius);
	Quad CreateQuad(float x, float y, float width, float height, float pivotX, float pivotY, const UV& uv = UV());
	Line2D CreateLine2D(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
	Triangle CreateTriangle(float origin, float scale);
	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness);
	UV GetTileUV(int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight);
	
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

		virtual void PreLoadTexture(const TextureAsset& texture) = 0;
		virtual void Submit(const Quad& renderable, const glm::vec4& color) = 0;
		virtual void Submit(const Quad& renderable, const TextureAsset& texture) = 0;
		virtual void Submit(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) = 0;
		virtual void Submit(const glm::vec2& pos, const glm::vec2& size, const TextureAsset& texture) = 0;
		virtual void Submit(const Triangle& renderable, const TextureAsset& texture) = 0;
		virtual void Submit(const Circle& renderable, const TextureAsset& texture) = 0;
		virtual void Submit(const ThickLine& renderable, const TextureAsset& texture) = 0;
		virtual void Submit(const Triangle& renderable, const glm::vec4& color) = 0;
		virtual void Submit(const Circle& renderable, const glm::vec4& color) = 0;
		virtual void Submit(const ThickLine& renderable, const glm::vec4& color) = 0;
		virtual void Submit(const Line2D& renderable) = 0;
		virtual void SubmitText(const std::string& text, float x, float y, float scale, const glm::vec3& color = glm::vec3(1.0f)) = 0;
		
		virtual void RenderFrameBuffer(uint32_t framebufferID, uint32_t width, uint32_t height) = 0;

		virtual void BeginBatch() = 0;
		virtual void EndBatch() = 0;

		virtual void Flush() = 0;
		virtual void Push(const glm::mat4& mat, boolean override = false);
		virtual void Pop();
		virtual void LoadFont(const std::string& fontPath, uint32_t size) = 0;
		virtual float ComputeTextWidth(const std::string& text, float scale) = 0;
		virtual void RenderText() = 0;
		virtual float GetFontHeight(float scale) = 0;
		virtual Shader* ExposeShader() const = 0;
		virtual void SetShader(Shader* shader) = 0;
		virtual void Begin(const std::weak_ptr<Camera>& cam) = 0;
	protected:
		Renderer2D() { m_TransformStack.push_back(glm::mat4(1.0f));
		m_TransformBack = &m_TransformStack.back();
		}

		std::vector<glm::mat4> m_TransformStack;
		const glm::mat4* m_TransformBack;
	};
}