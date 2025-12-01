#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Renderer/Core/Buffers.h"
#include "glad/glad.h"
#include "Dogo/Renderer/Core/Shader.h"
#include "Dogo/Renderer/Core/Texture.h"
#include "ft2build.h"
#include "Platform/OpenGL/OpenGLTextureArray.h"
#include "Dogo/Renderer/Core/Shader.h"
#include "Dogo/Systems/AssetSystem.h"
#include "Dogo/Utils/UUID.h"
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

		void RenderFrameBuffer(uint32_t framebufferID, uint32_t width, uint32_t height) override;
		void LoadTexture(const TextureAsset& texture) override;
		void Submit(const Quad& renderable, const glm::vec4& color) override;
		void Submit(const Quad& renderable, const TextureAsset& texture) override;
		void Submit(const Triangle& renderable, const TextureAsset& texture) override;
		void Submit(const Circle& renderable, const TextureAsset& texture) override;
		void Submit(const ThickLine& renderable, const TextureAsset& texture) override;
		void Submit(const Triangle& renderable, const glm::vec4& color) override;
		void Submit(const Circle& renderable, const glm::vec4& color) override;
		void Submit(const ThickLine& renderable, const glm::vec4& color) override;
		void Submit(const Line2D& renderable)override;
		void SubmitText(const std::string& text, float x, float y, float scale, const glm::vec3& color = glm::vec3(1.0f)) override;
		float ComputeTextWidth(const std::string& text, float scale) override;
		float GetFontHeight(float scale)override;
		void Flush()override;

		void Begin(const std::weak_ptr<Camera>& cam) override;

		inline Shader* ExposeShader() const override {
			return m_SpriteShader;
		}
		inline void SetShader(Shader* shader) override {
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

		Shader* m_TextShader;
		Shader* m_SpriteShader;
		Shader* m_FBShader;
		Shader* m_2DLineShader;

		
		std::vector<std::unique_ptr<OpenGLTextureArray>> m_TextureArrays;
		// UUID of texture, layer
		std::unordered_map<Dogo::UUID, TextureRef> UUIDToTextureRef;
		std::vector<Batch> m_ArrayBatches;
	};

}