#pragma once
#include "Dogo/Core.h"
#include "Dogo/Utils/Logger.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Core/Texture.h"
#include "Dogo/Renderer/Core/Shader.h"
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

		virtual void Submit(const Quad& renderable, const glm::vec4& color) = 0;
		virtual void Submit(const Quad& renderable, uint32_t texture) = 0;
		virtual void Submit(const Triangle& renderable, uint32_t texture) = 0;
		virtual void Submit(const Circle& renderable, uint32_t texture) = 0;
		virtual void Submit(const ThickLine& renderable, uint32_t texture) = 0;
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


		static constexpr const size_t Quad_MaxCount = 1000;
		static constexpr const size_t Quad_MaxVertexCount = Quad_MaxCount * 4;
		static constexpr const size_t Quad_MaxIndexCount = Quad_MaxCount * 6;

		static constexpr const size_t Triangle_MaxCount = 1000;
		static constexpr const size_t Triangle_MaxVertexCount = Triangle_MaxCount * 3;
		static constexpr const size_t Triangle_MaxIndexCount = Triangle_MaxCount * 3;

		static constexpr const size_t Circle_MaxCount = 1000;
		static constexpr const size_t Circle_MaxVertexCount = Circle_MaxCount * RendererConstants::Circle_Vertices;
		static constexpr const size_t Circle_MaxIndexCount = Circle_MaxCount * RendererConstants::Circle_Indices;

		static constexpr const size_t ThickLine_MaxCount = 1000;
		static constexpr const size_t ThickLine_MaxVertexCount = ThickLine_MaxCount * 4;
		static constexpr const size_t ThickLine_MaxIndexCount = ThickLine_MaxCount * 6;

		static constexpr const size_t Line2D_MaxCount = 1000;
		static constexpr const size_t Line2D_MaxVertexCount = Line2D_MaxCount * 2;

		int32_t Samplers[RendererConstants::MaxTextures] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	};

	Circle GenerateCircle(glm::vec2 center, float radius, float tiling = 1.0f);
	Quad CreateQuad(float x, float y, float width, float height, float pivotX, float pivotY, const UV& uv = UV(), float tiling = 1.0f);
	Line2D CreateLine2D(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
	Triangle CreateTriangle(float origin, float scale, float tiling = 1.0f);
	ThickLine CreateThickLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, float tiling = 1.0f);
}