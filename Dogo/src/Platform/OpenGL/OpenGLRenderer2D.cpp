#include "dgpch.h"
#include "OpenGLRenderer2D.h"
#include <glm/gtx/string_cast.hpp>
namespace Dogo
{

	OpenGLRenderer2D::OpenGLRenderer2D(const std::wstring& vertex, const std::wstring& pixel) : Renderer2D()
	{
		QuadBuffer = new Vertex[Quad_MaxVertexCount];
		QuadBufferPtr = QuadBuffer;

		TriangleBuffer = new Vertex[Triangle_MaxVertexCount];
		TriangleBufferPtr = TriangleBuffer;

		CircleBuffer = new Vertex[Circle_MaxVertexCount];
		CircleBufferPtr = CircleBuffer;

		ThickLineBuffer = new Vertex[ThickLine_MaxVertexCount];
		ThickLineBufferPtr = ThickLineBuffer;

		Line2DBuffer = new LineVertex[Line2D_MaxVertexCount];
		Line2DBufferPtr = Line2DBuffer;


		//	QUADS
		glCreateVertexArrays(1, &m_QuadsVertexArray);
		glBindVertexArray(m_QuadsVertexArray);

		glCreateBuffers(1, &m_QuadsVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, Quad_MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texInfo));


		{
			uint32_t indices[Quad_MaxIndexCount];
			uint32_t offset = 0;
			for (uint32_t i = 0; i < Quad_MaxIndexCount; i += 6)
			{
				indices[i + 0] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;

				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;
				offset += 4;
			}

			glCreateBuffers(1, &m_QuadsIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadsIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		//TRIANGLES

		glCreateVertexArrays(1, &m_TrianglesVertexArray);
		glBindVertexArray(m_TrianglesVertexArray);

		glCreateBuffers(1, &m_TrianglesVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, Triangle_MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texInfo));

		{
			uint32_t indices[Triangle_MaxIndexCount];
			uint32_t offset = 0;
			for (size_t i = 0, v = 0; i < Triangle_MaxIndexCount; i += 3)
			{
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				offset += 3;
			}

			glCreateBuffers(1, &m_TrianglesIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		//CIRCLES
		glCreateVertexArrays(1, &m_CirclesVertexArray);
		glBindVertexArray(m_CirclesVertexArray);

		glCreateBuffers(1, &m_CirclesVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_CirclesVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, Circle_MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texInfo));
		{
			uint32_t indices[Circle_MaxIndexCount];
			uint32_t offset = 0;
			for (size_t c = 0; c < Circle_MaxCount; ++c)
			{
				for (uint32_t i = 0; i < RendererConstants::Circle_Segments; ++i)
				{
					indices[(c * RendererConstants::Circle_Segments + i) * 3 + 0] = offset + 0;
					indices[(c * RendererConstants::Circle_Segments + i) * 3 + 1] = offset + i + 1;
					indices[(c * RendererConstants::Circle_Segments + i) * 3 + 2] = offset + i + 2;
				}
				offset += (RendererConstants::Circle_Segments + 2);
			}
			glCreateBuffers(1, &m_CirclesIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CirclesIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		//THICK LINES
		glCreateVertexArrays(1, &m_ThickLineVertexArray);
		glBindVertexArray(m_ThickLineVertexArray);

		glCreateBuffers(1, &m_ThickLineVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_ThickLineVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, ThickLine_MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texInfo));
		{
			uint32_t indices[ThickLine_MaxIndexCount];
			uint32_t offset = 0;
			for (size_t i = 0; i < ThickLine_MaxIndexCount; i += 6)
			{
				indices[i + 0] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;
				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;
				offset += 4;
			}
			glCreateBuffers(1, &m_ThickLineIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ThickLineIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}
		
		// LINES
		glCreateVertexArrays(1, &m_LinesVertexArray);
		glBindVertexArray(m_LinesVertexArray);


		glCreateBuffers(1, &m_LinesVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, Line2D_MaxVertexCount * sizeof(LineVertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, color));
		
		m_2DLineShader = Shader::Create(L"../Dogo/resources/Shaders/Line2Dvertex.glsl",
			L"../Dogo/resources/Shaders/Line2Dpixel.glsl");
		m_SpriteShader = Shader::Create(vertex, pixel);
		m_FBShader = Shader::Create(L"../Dogo/resources/Shaders/FBvertex.glsl",
			L"../Dogo/resources/Shaders/FBpixel.glsl");
		m_TextShader = Shader::Create(L"../Dogo/resources/Shaders/freetypevertex.glsl",
			L"../Dogo/resources/Shaders/freetypepixel.glsl");

		glGenVertexArrays(1, &m_FontVertexArray);
		glGenBuffers(1, &m_FontVertexBuffer);
		glBindVertexArray(m_FontVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_FontVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * RendererConstants::Max_Characters, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		LoadFont("../Dogo/resources/Fonts/arial.ttf", 48);

		glDisable(GL_DEPTH_TEST);
		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLRenderer2D::~OpenGLRenderer2D()
	{
		glDeleteVertexArrays(1, &m_QuadsVertexArray);
		glDeleteBuffers(1, &m_QuadsVertexBuffer);
		glDeleteBuffers(1, &m_QuadsIndexBuffer);

		delete[] QuadBuffer;
	}

	void OpenGLRenderer2D::SetViewMatrix(const glm::mat4& view)
	{
		m_View = view;
	}
	void OpenGLRenderer2D::SetProjectionMatrix(const glm::mat4& proj)
	{
		m_Proj = proj;
	}
	void OpenGLRenderer2D::SetModelMatrix(const glm::mat4& model)
	{
		m_Model = model;
	}
	void OpenGLRenderer2D::SetTransformMatrix(const glm::mat4& model)
	{
		m_Transform = model;
	}
	glm::mat4 OpenGLRenderer2D::GetViewMatrix()
	{
		return m_View;
	}
	glm::mat4 OpenGLRenderer2D::GetProjectionMatrix()
	{
		return m_Proj;
	}
	glm::mat4 OpenGLRenderer2D::GetModelMatrix()
	{
		return m_Model;
	}
	glm::mat4 OpenGLRenderer2D::GetTransformMatrix()
	{
		return m_Transform;
	}
	void OpenGLRenderer2D::SetViewPos(const glm::vec3& pos)
	{
		m_ViewPos = pos;
	}

	void OpenGLRenderer2D::Submit(const Quad& renderable, const TextureAsset& texture)
	{
		auto it = UUIDToTextureRef.find(texture.GetUUID());
		if (it == UUIDToTextureRef.end())
		{
			LoadTexture(texture);
		}
		auto tex = UUIDToTextureRef[texture.GetUUID()];
		if (m_TextureArrays[tex.arrayID]->GetLayerCount() >= RendererConstants::MaxTextures)
		{
			DG_ERROR("Max textures reached.\n");
			return;
		}
		if (Quad_IndexCount >= Quad_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		glm::vec2 texInfo = glm::vec2(tex.arrayID, tex.layer);
		for (size_t i = 0; i < 4; i++)
		{
			QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			QuadBufferPtr->color = color;
			QuadBufferPtr->texcoord = { renderable.vertices[i].texcoord.x, renderable.vertices[i].texcoord.y };
			QuadBufferPtr->texInfo = texInfo;
			QuadBufferPtr++;
		}

		Quad_IndexCount += 6;
	}
	void OpenGLRenderer2D::Submit(const Quad& renderable, const glm::vec4& color)
	{
		if (Quad_IndexCount >= Quad_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec2 texInfo = glm::vec2(0.0f, 0.0f);
		for (size_t i = 0; i < 4; i++)
		{
			QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			QuadBufferPtr->color = color;
			QuadBufferPtr->texcoord = { renderable.vertices[i].texcoord.x, renderable.vertices[i].texcoord.y };
			QuadBufferPtr->texInfo = texInfo;
			QuadBufferPtr++;
		}
		Quad_IndexCount += 6;
	}

	void OpenGLRenderer2D::Submit(const Triangle& renderable, const TextureAsset& texture)
	{
		auto it = UUIDToTextureRef.find(texture.GetUUID());
		if (it == UUIDToTextureRef.end())
		{
			LoadTexture(texture);
		}
		auto tex = UUIDToTextureRef[texture.GetUUID()];
		if (m_TextureArrays[tex.arrayID]->GetLayerCount() >= RendererConstants::MaxTextures)
		{
			DG_ERROR("Max textures reached.\n");
			return;
		}
		if (Triangle_IndexCount >= Triangle_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		glm::vec2 texInfo = glm::vec2(tex.arrayID, tex.layer);
		for (size_t i = 0; i < 3; i++)
		{
			TriangleBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			TriangleBufferPtr->color = color;
			TriangleBufferPtr->texcoord = renderable.vertices[i].texcoord;
			TriangleBufferPtr->texInfo = texInfo;
			TriangleBufferPtr++;
		}

		Triangle_IndexCount += 3;
	}
	void OpenGLRenderer2D::Submit(const Triangle& renderable, const glm::vec4& color)
	{
		if (Triangle_IndexCount >= Triangle_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec2 texInfo = glm::vec2(0.0f, 0.0f);
		for (size_t i = 0; i < 3; i++)
		{
			TriangleBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			TriangleBufferPtr->color = color;
			TriangleBufferPtr->texcoord = renderable.vertices[i].texcoord;
			TriangleBufferPtr->texInfo = texInfo;
			TriangleBufferPtr++;
		}

		Triangle_IndexCount += 3;
	}
	void OpenGLRenderer2D::Submit(const Circle& renderable, const TextureAsset& texture)
	{
		auto it = UUIDToTextureRef.find(texture.GetUUID());
		if (it == UUIDToTextureRef.end())
		{
			LoadTexture(texture);
		}
		auto tex = UUIDToTextureRef[texture.GetUUID()];
		if (m_TextureArrays[tex.arrayID]->GetLayerCount() >= RendererConstants::MaxTextures)
		{
			DG_ERROR("Max textures reached.\n");
			return;
		}
		if (Circle_IndexCount >= Circle_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		glm::vec2 texInfo = glm::vec2(tex.arrayID, tex.layer);
		for (size_t i = 0; i < RendererConstants::Circle_Vertices; i++)
		{
			CircleBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			CircleBufferPtr->color = color;
			CircleBufferPtr->texcoord = renderable.vertices[i].texcoord;
			CircleBufferPtr->texInfo = texInfo;
			CircleBufferPtr++;
		}

		Circle_IndexCount += RendererConstants::Circle_Indices;
	}
	void OpenGLRenderer2D::Submit(const Circle& renderable, const glm::vec4& color)
	{
		if (Circle_IndexCount >= Circle_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec2 texInfo = glm::vec2(0.0f, 0.0f);
		for (size_t i = 0; i < RendererConstants::Circle_Vertices; i++)
		{
			CircleBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			CircleBufferPtr->color = color;
			CircleBufferPtr->texcoord = renderable.vertices[i].texcoord;
			CircleBufferPtr->texInfo = texInfo;
			CircleBufferPtr++;
		}

		Circle_IndexCount += RendererConstants::Circle_Indices;
	}
	void OpenGLRenderer2D::Submit(const ThickLine& renderable, const TextureAsset& texture)
	{
		auto it = UUIDToTextureRef.find(texture.GetUUID());
		if (it == UUIDToTextureRef.end())
		{
			LoadTexture(texture);
		}
		auto tex = UUIDToTextureRef[texture.GetUUID()];
		if (m_TextureArrays[tex.arrayID]->GetLayerCount() >= RendererConstants::MaxTextures)
		{
			DG_ERROR("Max textures reached.\n");
			return;
		}
		if (ThickLine_IndexCount >= ThickLine_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec4 color = { 1.0f,1.0f, 1.0f, 1.0f };
		glm::vec2 texInfo = glm::vec2(tex.arrayID, tex.layer);
		for (size_t i = 0; i < 4; i++)
		{
			ThickLineBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			ThickLineBufferPtr->color = color;
			ThickLineBufferPtr->texcoord = renderable.vertices[i].texcoord;
			ThickLineBufferPtr->texInfo = texInfo;
			ThickLineBufferPtr++;
		}

		ThickLine_IndexCount += 6;
	}
	void OpenGLRenderer2D::Submit(const ThickLine& renderable, const glm::vec4& color)
	{
		if (ThickLine_IndexCount >= ThickLine_MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		constexpr glm::vec2 texInfo = glm::vec2(0.0f, 0.0f);
		for (size_t i = 0; i < 4; i++)
		{
			ThickLineBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			ThickLineBufferPtr->color = color;
			ThickLineBufferPtr->texcoord = renderable.vertices[i].texcoord;
			ThickLineBufferPtr->texInfo = texInfo;
			ThickLineBufferPtr++;
		}

		ThickLine_IndexCount += 6;
	}
	void OpenGLRenderer2D::Submit(const Line2D& renderable)
	{
		if (Line2D_VertexCount >= Line2D_MaxVertexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}
		for (int i = 0; i < 2; i++)
		{
			Line2DBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
			Line2DBufferPtr->color = renderable.vertices[i].color;
			Line2DBufferPtr++;
		}
		Line2D_VertexCount +=2;
	}

	void OpenGLRenderer2D::RenderFrameBuffer(uint32_t framebufferID, uint32_t width, uint32_t height)
	{

		BeginBatch();
		QuadBufferPtr->position = { 0.0f, 0.0f , 0.0f };
		QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(QuadBufferPtr->position, 1.0f));
		QuadBufferPtr->color = glm::vec4(1.0f,1.0f, 1.0f, 1.0f);
		QuadBufferPtr->texcoord = { 0.0f, 0.0f };
		QuadBufferPtr->texInfo = { 0.0f, 0.0f };
		QuadBufferPtr++;

		QuadBufferPtr->position = { width, 0.0f , 0.0f };
		QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(QuadBufferPtr->position, 1.0f));
		QuadBufferPtr->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		QuadBufferPtr->texcoord = { 1.0f, 0.0f };
		QuadBufferPtr->texInfo = { 0.0f, 0.0f };
		QuadBufferPtr++;

		QuadBufferPtr->position = { width, height , 0.0f };
		QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(QuadBufferPtr->position, 1.0f));
		QuadBufferPtr->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		QuadBufferPtr->texcoord = { 1.0f, 1.0f };
		QuadBufferPtr->texInfo = { 0.0f, 0.0f };
		QuadBufferPtr++;

		QuadBufferPtr->position = { 0.0f, height, 0.0f };
		QuadBufferPtr->position = glm::vec3(*m_TransformBack * glm::vec4(QuadBufferPtr->position, 1.0f));
		QuadBufferPtr->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		QuadBufferPtr->texcoord = { 0.0f, 1.0f };
		QuadBufferPtr->texInfo = { 0.0f, 0.0f };
		QuadBufferPtr++;
		Quad_IndexCount += 6;
		EndBatch();
		m_FBShader->Bind();
		glBindTextureUnit(0, framebufferID);
		m_FBShader->SetUniform1i("texture2D", 0);
		m_FBShader->SetUniformMatrix4f("view", m_View);
		m_FBShader->SetUniformMatrix4f("projection", m_Proj);
		glBindVertexArray(m_QuadsVertexArray);
		glDrawElements(GL_TRIANGLES, Quad_IndexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer2D::LoadTexture(const TextureAsset& texture)
	{
		UUID id = texture.GetUUID();

		if (UUIDToTextureRef.find(id) != UUIDToTextureRef.end())
			return;

		for (size_t i = 0; i < m_TextureArrays.size(); i++)
		{
			if (texture.GetWidth() == m_TextureArrays[i]->GetWidth() &&
				texture.GetHeight() == m_TextureArrays[i]->GetHeight())
			{
				uint32_t layer = m_TextureArrays[i]->AddTexture(texture.GetPath().string());
				UUIDToTextureRef[id] = { uint32_t(i), layer };
				return;
			}
		}

		m_TextureArrays.emplace_back(
			new OpenGLTextureArray(texture.GetWidth(), texture.GetHeight(), 
			RendererConstants::MaxTextures)
		);
		m_TextureArrays.back()->AddWhiteLayer();
		uint32_t layer = m_TextureArrays.back()->AddTexture(texture.GetPath().string());
		UUIDToTextureRef[id] = { uint32_t(m_TextureArrays.size() - 1), layer };
	}

	void OpenGLRenderer2D::Flush()
	{
		if (Line2D_VertexCount)
		{
			m_2DLineShader->Bind();
			m_2DLineShader->SetUniformMatrix4f("view", m_View);
			m_2DLineShader->SetUniformMatrix4f("projection", m_Proj);
			glBindVertexArray(m_LinesVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
			glDrawArrays(GL_LINES, 0, Line2D_VertexCount);
		}
		m_SpriteShader->Bind();
		m_SpriteShader->SetUniform1iv("textureArrays", &SamplerArrays[0], RendererConstants::MaxTextures);
		m_SpriteShader->SetUniformMatrix4f("view", m_View);
		m_SpriteShader->SetUniformMatrix4f("projection", m_Proj);
		for (int i = 0; i < m_TextureArrays.size(); ++i)
			glBindTextureUnit(i, m_TextureArrays[i]->GetID());

		if (ThickLine_IndexCount)
		{
			glBindVertexArray(m_ThickLineVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_ThickLineVertexBuffer);
			glDrawElements(GL_TRIANGLES, ThickLine_IndexCount, GL_UNSIGNED_INT, nullptr);
		}
		if (Circle_IndexCount)
		{
			glBindVertexArray(m_CirclesVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_CirclesVertexBuffer);
			glDrawElements(GL_TRIANGLES, Circle_IndexCount, GL_UNSIGNED_INT, nullptr);
		}
		if (Triangle_IndexCount)
		{
			glBindVertexArray(m_TrianglesVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesVertexBuffer);
			glDrawElements(GL_TRIANGLES, Triangle_IndexCount, GL_UNSIGNED_INT, nullptr);
		}
		if (Quad_IndexCount)
		{
			glBindVertexArray(m_QuadsVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
			glDrawElements(GL_TRIANGLES, Quad_IndexCount, GL_UNSIGNED_INT, nullptr);
		}

	}
	void OpenGLRenderer2D::Begin(const std::weak_ptr<Camera>& cam)
	{
		if (!cam.expired())
		{
			m_View = cam.lock()->GetViewMatrix();
			m_Proj = cam.lock()->GetProjectionMatrix();
		}
	}
	float OpenGLRenderer2D::GetFontHeight(float scale)
	{
		auto it = Characters.find('H');
		if (it != Characters.end())
			return it->second.size.y * scale;
		return 0.0f;
	}
	float OpenGLRenderer2D::ComputeTextWidth(const std::string& text, float scale)
	{
		float width = 0.0f;
		for (char c : text)
		{
			auto it = Characters.find(c);
			if (it != Characters.end())
			{
				const Character& ch = it->second;
				width += (ch.advance >> 6) * scale; // Convert from 1/64th pixels
			}
		}
		return width;
	}
	void OpenGLRenderer2D::LoadFont(const std::string& fontPath, uint32_t size)
	{

		Characters.clear();

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		FT_Face face;
		if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			FT_Done_FreeType(ft);
			return;
		}

		FT_Set_Pixel_Sizes(face, 0, size);

		int atlasWidth = 0;
		int atlasHeight = 0;
		int rowHeight = 0;

		for (GLubyte c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				continue;

			if (atlasWidth + face->glyph->bitmap.width >= 1024)
			{
				atlasHeight += rowHeight;
				atlasWidth = 0;
				rowHeight = 0;
			}

			atlasWidth += face->glyph->bitmap.width + 1;
			rowHeight = std::max(rowHeight, static_cast<int>(face->glyph->bitmap.rows));
		}

		atlasHeight += rowHeight;

		GLuint atlasTex;
		glGenTextures(1, &atlasTex);
		glBindTexture(GL_TEXTURE_2D, atlasTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1024, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int xOffset = 0;
		int yOffset = 0;
		rowHeight = 0;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Failed to load Glyph " << (char)c << std::endl;
				continue;
			}

			if (xOffset + face->glyph->bitmap.width >= 1024)
			{
				yOffset += rowHeight;
				xOffset = 0;
				rowHeight = 0;
			}

			glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				GL_RED, GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);

			float u0 = (float)xOffset / 1024.0f;
			float v0 = (float)yOffset / (float)atlasHeight;              // bottom
			float u1 = (float)(xOffset + face->glyph->bitmap.width) / 1024.0f;
			float v1 = (float)(yOffset + face->glyph->bitmap.rows) / atlasHeight; // top



			Character character = {
				glm::vec2(u0, v0),
				glm::vec2(u1, v1),
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			Characters.insert(std::pair<char, Character>(c, character));
			xOffset += face->glyph->bitmap.width + 1;
			rowHeight = std::max(rowHeight, static_cast<int>(face->glyph->bitmap.rows));
		}

		m_FontAtlasTextureID = atlasTex;

		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
	void OpenGLRenderer2D::SubmitText(const std::string& text, float x, float y, float scale, const glm::vec3& color)
	{
		TextCommand cmd;
		cmd.text = text;
		cmd.x = x;
		cmd.y = y;
		cmd.scale = scale;
		cmd.color = color;
		cmd.transform = *m_TransformBack;
		m_TextCommands.push_back(cmd);
	}

	void OpenGLRenderer2D::RenderText()
	{
		if (m_TextCommands.empty()) return;

		glDepthFunc(GL_ALWAYS);
		m_TextShader->Bind();
		m_TextShader->SetUniformMatrix4f("projection", m_Proj);
		m_TextShader->SetUniformMatrix4f("view", m_View);
		m_TextShader->SetUniform1i("text", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_FontAtlasTextureID);
		glBindVertexArray(m_FontVertexArray);

		std::vector<float> vertices;
		vertices.reserve(m_TextCommands.size() * 6 * 4 * 16);

		for (const auto& cmd : m_TextCommands)
		{
			float cursorX = cmd.x;
			float cursorY = cmd.y;

			glm::vec4 transformedPos = cmd.transform * glm::vec4(cursorX, cursorY, 0.0f, 1.0f);
			cursorX = transformedPos.x;
			cursorY = transformedPos.y;

			for (char c : cmd.text)
			{
				const Character& ch = Characters.at(c);
				float xpos = cursorX + ch.bearing.x;
				float ypos = cursorY - (ch.size.y - ch.bearing.y);

				float w = ch.size.x;
				float h = ch.size.y;

				float u0 = ch.uvTopLeft.x;
				float v0 = ch.uvTopLeft.y;
				float u1 = ch.uvBottomRight.x;
				float v1 = ch.uvBottomRight.y;

				float quad[6][4] = {
					{ xpos,     ypos + h, u0, v0 },
					{ xpos + w, ypos,     u1, v1 },
					{ xpos,     ypos,     u0, v1 },

					{ xpos,     ypos + h, u0, v0 },
					{ xpos + w, ypos + h, u1, v0 },
					{ xpos + w, ypos,     u1, v1 }
				};



				vertices.insert(vertices.end(), &quad[0][0], &quad[0][0] + 6 * 4);
				cursorX += (ch.advance >> 6) * cmd.scale;
			}

			m_TextShader->SetUniform3f("textColor", cmd.color);
			glBindBuffer(GL_ARRAY_BUFFER, m_FontVertexBuffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 4));
			vertices.clear();
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_TextCommands.clear();
	}

	void OpenGLRenderer2D::BeginBatch()
	{
		QuadBufferPtr = QuadBuffer;
		Quad_IndexCount = 0;

		Line2DBufferPtr = Line2DBuffer;
		Line2D_VertexCount = 0;

		TriangleBufferPtr = TriangleBuffer;
		Triangle_IndexCount = 0;

		CircleBufferPtr = CircleBuffer;
		Circle_IndexCount = 0;

		ThickLineBufferPtr = ThickLineBuffer;
		ThickLine_IndexCount = 0;
	}

	void OpenGLRenderer2D::EndBatch()
	{
		GLsizeiptr quadsize =(uint32_t)((uint8_t*)QuadBufferPtr - (uint8_t*)QuadBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, quadsize, QuadBuffer);

		GLsizeiptr line2dsize = (uint32_t)((uint8_t*)Line2DBufferPtr - (uint8_t*)Line2DBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, line2dsize, Line2DBuffer);

		GLsizeiptr trianglesize = (uint32_t)((uint8_t*)TriangleBufferPtr - (uint8_t*)TriangleBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, trianglesize, TriangleBuffer);

		GLsizeiptr circlesize = (uint32_t)((uint8_t*)CircleBufferPtr - (uint8_t*)CircleBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_CirclesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, circlesize, CircleBuffer);

		GLsizeiptr thicklinesize = (uint32_t)((uint8_t*)ThickLineBufferPtr - (uint8_t*)ThickLineBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_ThickLineVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, thicklinesize, ThickLineBuffer);
	}
	
}