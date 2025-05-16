#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/Buffers.h"
#include "glad/glad.h"
#include "Dogo/Renderer/Shader.h"
#include "Dogo/Renderer/Texture.h"
#include "ft2build.h"
#include "Dogo/Renderer/Shader.h"
#include FT_FREETYPE_H
namespace Dogo
{
	class OpenGLRenderer2D : public Renderer2D
	{
	public:
		OpenGLRenderer2D(const std::wstring& vertex, const std::wstring& pixel);
		~OpenGLRenderer2D();

		void SetViewMatrix(const glm::mat4& view)override;
		void SetProjectionMatrix(const glm::mat4& proj)override;
		void SetModelMatrix(const glm::mat4& model)override;
		void SetTransformMatrix(const glm::mat4& model)override;

		glm::mat4 GetViewMatrix()override;
		glm::mat4 GetProjectionMatrix()override;
		glm::mat4 GetModelMatrix()override;
		glm::mat4 GetTransformMatrix()override;

		void SetViewPos(const glm::vec3& pos)override;

		void Submit(Quad& renderable, Texture* tex = nullptr) override;
		void Submit(Triangle& renderable, Texture* tex = nullptr) override;
		void Submit(Circle& renderable, Texture* tex = nullptr) override;
		void Submit(RoundedRect& renderable, Texture* tex = nullptr) override;
		void Submit(ThickLine& renderable, Texture* tex = nullptr) override;
		void Submit(Line2D& renderable)override;

		void Flush()override;

		virtual void LoadFont(const std::string& fontPath, uint32_t size);
		virtual void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

	private:
		void LinesFlush();
		void QuadsFlush();
		void TrianglesFlush();
		void CirclesFlush();
		void RoundedRectFlush();
		void ThickLineFlush();

	protected:
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Proj = glm::mat4(1.0f);
		glm::mat4 m_Model = glm::mat4(1.0f);
		glm::mat4 m_Transform = glm::mat4(1.0f);
		glm::vec3 m_ViewPos{};

		GLuint m_QuadsVertexArray{};
		GLuint m_QuadsVertexBuffer{};
		GLuint m_QuadsIndexBuffer{};

		GLuint m_LinesVertexArray{};
		GLuint m_LinesVertexBuffer{};
		GLuint m_LinesIndexBuffer{};

		GLuint m_TrianglesVertexArray{};
		GLuint m_TrianglesVertexBuffer{};
		GLuint m_TrianglesIndexBuffer{};

		GLuint m_CirclesVertexArray{};
		GLuint m_CirclesVertexBuffer{};
		GLuint m_CirclesIndexBuffer{};

		GLuint m_RoundedRectVertexArray{};
		GLuint m_RoundedRectVertexBuffer{};
		GLuint m_RoundedRectIndexBuffer{};

		GLuint m_ThickLineVertexArray{};
		GLuint m_ThickLineVertexBuffer{};
		GLuint m_ThickLineIndexBuffer{};

		GLuint m_FontVertexArray{};
		GLuint m_FontVertexBuffer{};
		std::map<char, Character> Characters;
		GLuint FontAtlasTextureID = 0;

		Shader* m_TextShader;
		Shader* m_Shader;

		std::array<Quad, MAX_QUADS> m_QuadsBuffer;
		size_t m_QuadsCount = 0;
		std::array<uint32_t, MAX_QUAD_INDICES> m_QuadsIndices;

		std::array<Line2D, MAX_LINES> m_LinesBuffer;
		size_t m_LinesCount = 0;
		std::array<uint32_t, MAX_LINE_INDICES> m_LinesIndices;

		std::array<Triangle, MAX_TRIANGLES> m_TrianglesBuffer;
		size_t m_TrianglesCount = 0;
		std::array<uint32_t, MAX_TRIANGLE_INDICES> m_TrianglesIndices;

		std::array<Circle, MAX_CIRCLES> m_CirclesBuffer;
		size_t m_CirclesCount = 0;
		std::array<uint32_t, MAX_CIRCLE_INDICES> m_CirclesIndices;

		std::array<RoundedRect, MAX_ROUNDED_RECTS> m_RoundedRectsBuffer;
		size_t m_RoundedRectsCount = 0;
		std::array<uint32_t, MAX_ROUNDED_RECT_INDICES> m_RoundedRectsIndices;

		std::array<ThickLine, MAX_ROUNDED_RECTS> m_ThickLinesBuffer;
		size_t m_ThickLinesCount = 0;
		std::array<uint32_t, MAX_ROUNDED_RECT_INDICES> m_ThickLinesIndices;

		std::vector<std::pair<Texture*, uint16_t>> m_TextureSlots;
		int m_Samplers[TWO_D_MAX_TEXTURES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	};

}