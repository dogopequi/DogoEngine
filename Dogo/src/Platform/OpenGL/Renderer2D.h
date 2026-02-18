#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "GraphicsPipeline.h"
#include "glad/glad.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "Texture2D.h"
#include "Dogo/Systems/AssetSystem.h"
#include "Dogo/Utils/UUID.h"
#include "Dogo/Renderer/2D/2DUtils.h"
#include "ft2build.h"
#include FT_FREETYPE_H


namespace std {
	template<>
	struct hash<Dogo::UUID> {
		std::size_t operator()(const Dogo::UUID& uuid) const noexcept {
			return std::hash<uint64_t>()(uuid.GetUUID_ui64());
		}
	};
}
namespace Dogo
{
	class Renderer2D
	{
	public:
		Renderer2D(const std::filesystem::path& vertex, const std::filesystem::path& pixel);
		~Renderer2D();

		void SetViewMatrix(const glm::mat4& view);
		void SetProjectionMatrix(const glm::mat4& proj);
		void SetModelMatrix(const glm::mat4& model);
		void SetTransformMatrix(const glm::mat4& model);

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetModelMatrix();
		glm::mat4 GetTransformMatrix();

		void SetViewPos(const glm::vec3& pos);

		void RenderFrameBuffer(uint32_t framebufferID, uint32_t width, uint32_t height) ;
		void Submit(const Quad& renderable, const glm::vec4& color) ;
		void Submit(const Quad& renderable, uint32_t texture) ;
		void Submit(const Triangle& renderable, uint32_t texture) ;
		void Submit(const Circle& renderable, uint32_t texture) ;
		void Submit(const ThickLine& renderable, uint32_t texture) ;
		void Submit(const Triangle& renderable, const glm::vec4& color) ;
		void Submit(const Circle& renderable, const glm::vec4& color) ;
		void Submit(const ThickLine& renderable, const glm::vec4& color) ;
		void Submit(const Line2D& renderable);
		void SubmitText(const std::string& text, float x, float y, float scale, const glm::vec3& color = glm::vec3(1.0f)) ;
		float ComputeTextWidth(const std::string& text, float scale) ;
		float GetFontHeight(float scale);
		void Flush();
		inline void Push(const glm::mat4& mat, bool override = false)
		{
			if (override)
				m_TransformStack.push_back(mat);
			else
				m_TransformStack.push_back(mat * m_TransformStack.back());
			m_TransformBack = &m_TransformStack.back();
		}

		inline void Pop()
		{
			if (m_TransformStack.size() > 1)
			{
				m_TransformStack.pop_back();
			}
			m_TransformBack = &m_TransformStack.back();
		}

		inline glm::mat4 GetTransformBack() const
		{
			return *m_TransformBack;
		}

		void Begin(const std::weak_ptr<Camera>& cam) ;

		inline GraphicsPipeline* ExposeGraphicsPipeline() const  {
			return m_SpriteShader;
		}
		inline void SetShader(GraphicsPipeline* shader)  {
			m_SpriteShader = shader;
		}

		void LoadFont(const std::string& fontPath, uint32_t size);
		void RenderText();

		void BeginBatch();
		void EndBatch();

	protected:
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Proj = glm::mat4(1.0f);
		glm::mat4 m_Model = glm::mat4(1.0f);
		glm::mat4 m_Transform = glm::mat4(1.0f);
		glm::vec3 m_ViewPos{};

		uint32_t Quad_IndexCount = 0;
		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;
		GLuint m_QuadsVertexArray{};
		GLuint m_QuadsVertexBuffer{};
		GLuint m_QuadsIndexBuffer{};

		uint32_t Triangle_IndexCount = 0;
		Vertex* TriangleBuffer = nullptr;
		Vertex* TriangleBufferPtr = nullptr;
		GLuint m_TrianglesVertexArray{};
		GLuint m_TrianglesVertexBuffer{};
		GLuint m_TrianglesIndexBuffer{};

		uint32_t Circle_IndexCount = 0;
		Vertex* CircleBuffer = nullptr;
		Vertex* CircleBufferPtr = nullptr;
		GLuint m_CirclesVertexArray{};
		GLuint m_CirclesVertexBuffer{};
		GLuint m_CirclesIndexBuffer{};

		uint32_t ThickLine_IndexCount = 0;
		Vertex* ThickLineBuffer = nullptr;
		Vertex* ThickLineBufferPtr = nullptr;
		GLuint m_ThickLineVertexArray{};
		GLuint m_ThickLineVertexBuffer{};
		GLuint m_ThickLineIndexBuffer{};

		LineVertex* Line2DBuffer = nullptr;
		LineVertex* Line2DBufferPtr = nullptr;
		uint32_t Line2D_VertexCount = 0;
		GLuint m_LinesVertexArray{};
		GLuint m_LinesVertexBuffer{};

		GLuint m_FontVertexArray{};
		GLuint m_FontVertexBuffer{};
		std::map<char, Character> Characters;
		GLuint m_FontAtlasTextureID = 0;
		std::vector<TextCommand> m_TextCommands;

		GraphicsPipeline* m_TextShader;
		GraphicsPipeline* m_SpriteShader;
		GraphicsPipeline* m_FBShader;
		GraphicsPipeline* m_2DLineShader;

		std::vector<glm::mat4> m_TransformStack;
		const glm::mat4* m_TransformBack;

		GLuint m_WhiteTexture = 0;
		const uint32_t c_WhiteTextureSlot = 0;
		uint32_t m_TextureSlotIndex = 1;
		std::array<uint32_t, RendererConstants::MaxTextures> m_TextureSlots;


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

}