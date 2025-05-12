#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/Buffers.h"
#include "glad/glad.h"
#include "Dogo/Renderer/Shader.h"
#include "Dogo/Renderer/Texture.h"
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
		void Submit(Quad& renderable, Texture* tex = nullptr)override;
		void Submit(const Line2D& renderable)override;
		void Flush()override;;

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

		Shader* m_Shader;
		std::array<Quad, MAX_QUADS> m_QuadsBuffer;
		size_t m_QuadsCount = 0;
		std::array<uint32_t, MAX_QUAD_INDICES> m_QuadsIndices;
		std::vector<std::pair<Texture*, uint16_t>> m_TextureSlots;
		int m_Samplers[TWO_D_MAX_TEXTURES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	};

}