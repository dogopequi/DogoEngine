#include "dgpch.h"
#include "OpenGLRenderer2D.h"
#include <glm/gtx/string_cast.hpp>
namespace Dogo{
	OpenGLRenderer2D::OpenGLRenderer2D(const std::wstring& vertex, const std::wstring& pixel) : Renderer2D()
	{
		//////////QUADS
		{
			glCreateVertexArrays(1, &m_QuadsVertexArray);
			glBindVertexArray(m_QuadsVertexArray);


			glCreateBuffers(1, &m_QuadsVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_QUAD_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_QuadsVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(m_QuadsVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(m_QuadsVertexArray, 2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
			glEnableVertexArrayAttrib(m_QuadsVertexArray, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
			glEnableVertexArrayAttrib(m_QuadsVertexArray, 4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

			uint32_t offset = 0;
			for (size_t i = 0; i < MAX_QUAD_INDICES; i += 6)
			{
				m_QuadsIndices[i + 0] = 0 + offset;
				m_QuadsIndices[i + 1] = 1 + offset;
				m_QuadsIndices[i + 2] = 2 + offset;
				m_QuadsIndices[i + 3] = 2 + offset;
				m_QuadsIndices[i + 4] = 3 + offset;
				m_QuadsIndices[i + 5] = 0 + offset;
				offset += 4;
			}

			glCreateBuffers(1, &m_QuadsIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadsIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_QuadsIndices), m_QuadsIndices.data(), GL_STATIC_DRAW);

		}
		//////////// TRIANGLES
		{
			glCreateVertexArrays(1, &m_TrianglesVertexArray);
			glBindVertexArray(m_TrianglesVertexArray);


			glCreateBuffers(1, &m_TrianglesVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_TRIANGLE_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_TrianglesVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(m_TrianglesVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(m_TrianglesVertexArray, 2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
			glEnableVertexArrayAttrib(m_TrianglesVertexArray, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
			glEnableVertexArrayAttrib(m_TrianglesVertexArray, 4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

			for (size_t i = 0, v = 0; i < MAX_TRIANGLE_INDICES; i += 3, v += 3)
			{
				m_TrianglesIndices[i + 0] = v + 0;
				m_TrianglesIndices[i + 1] = v + 1;
				m_TrianglesIndices[i + 2] = v + 2;
			}

			glCreateBuffers(1, &m_TrianglesIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_TrianglesIndices), m_TrianglesIndices.data(), GL_STATIC_DRAW);

		}
		/////////// CIRCLES
		{
			glCreateVertexArrays(1, &m_CirclesVertexArray);
			glBindVertexArray(m_CirclesVertexArray);


			glCreateBuffers(1, &m_CirclesVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_CirclesVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_CIRCLE_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_CirclesVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(m_CirclesVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(m_CirclesVertexArray, 2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
			glEnableVertexArrayAttrib(m_CirclesVertexArray, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
			glEnableVertexArrayAttrib(m_CirclesVertexArray, 4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

			uint32_t offset = 0;
			for (size_t c = 0; c < MAX_CIRCLES; ++c)
			{
				for (uint32_t i = 0; i < CIRCLE_SEGMENTS; ++i)
				{
					m_CirclesIndices[(c * CIRCLE_SEGMENTS + i) * 3 + 0] = offset + 0;
					m_CirclesIndices[(c * CIRCLE_SEGMENTS + i) * 3 + 1] = offset + i + 1;
					m_CirclesIndices[(c * CIRCLE_SEGMENTS + i) * 3 + 2] = offset + i + 2;
				}
				offset += (CIRCLE_SEGMENTS + 2);
			}

			glCreateBuffers(1, &m_CirclesIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CirclesIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_CirclesIndices), m_CirclesIndices.data(), GL_STATIC_DRAW);

		}
		///////////// ROUNDED RECT
		{
			glCreateVertexArrays(1, &m_RoundedRectVertexArray);
			glBindVertexArray(m_RoundedRectVertexArray);


			glCreateBuffers(1, &m_RoundedRectVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_RoundedRectVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_ROUNDED_RECT_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_RoundedRectVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(m_RoundedRectVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(m_RoundedRectVertexArray, 2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
			glEnableVertexArrayAttrib(m_RoundedRectVertexArray, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
			glEnableVertexArrayAttrib(m_RoundedRectVertexArray, 4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

			uint32_t offset = 0;
			for (size_t r = 0; r < MAX_ROUNDED_RECTS; ++r)
			{
				uint32_t centerIndex = offset;
				uint32_t arcStart = offset + 1;

				for (int corner = 0; corner < 4; ++corner)
				{
					uint32_t cornerStart = arcStart + corner * (ROUNDED_RECT_SEGMENTS + 1);

					for (int seg = 0; seg < ROUNDED_RECT_SEGMENTS; ++seg)
					{
						uint32_t i0 = centerIndex;
						uint32_t i1 = cornerStart + seg;
						uint32_t i2 = cornerStart + seg + 1;

						size_t indexOffset = (r * ROUNDED_RECT_SEGMENTS * 4 + corner * ROUNDED_RECT_SEGMENTS + seg) * 3;
						m_RoundedRectsIndices[indexOffset + 0] = i0;
						m_RoundedRectsIndices[indexOffset + 1] = i1;
						m_RoundedRectsIndices[indexOffset + 2] = i2;
					}
				}

				offset += 1 + 4 * (ROUNDED_RECT_SEGMENTS + 1); 
			}


			glCreateBuffers(1, &m_RoundedRectIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RoundedRectIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_RoundedRectsIndices), m_RoundedRectsIndices.data(), GL_STATIC_DRAW);

		}
		////////////// THICK LINES
		{
			glCreateVertexArrays(1, &m_ThickLineVertexArray);
			glBindVertexArray(m_ThickLineVertexArray);


			glCreateBuffers(1, &m_ThickLineVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_ThickLineVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_QUAD_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_ThickLineVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexArrayAttrib(m_ThickLineVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
			glEnableVertexArrayAttrib(m_ThickLineVertexArray, 2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
			glEnableVertexArrayAttrib(m_ThickLineVertexArray, 3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
			glEnableVertexArrayAttrib(m_ThickLineVertexArray, 4);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

			uint32_t offset = 0;
			for (size_t i = 0; i < MAX_THICK_LINES_INDICES; i += 6)
			{
				m_ThickLinesIndices[i + 0] = 0 + offset;
				m_ThickLinesIndices[i + 1] = 1 + offset;
				m_ThickLinesIndices[i + 2] = 2 + offset;
				m_ThickLinesIndices[i + 3] = 2 + offset;
				m_ThickLinesIndices[i + 4] = 3 + offset;
				m_ThickLinesIndices[i + 5] = 0 + offset;
				offset += 4;
			}

			glCreateBuffers(1, &m_ThickLineIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ThickLineIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_ThickLinesIndices), m_ThickLinesIndices.data(), GL_STATIC_DRAW);
		}
		////////////// LINES
		{
			glCreateVertexArrays(1, &m_LinesVertexArray);
			glBindVertexArray(m_LinesVertexArray);


			glCreateBuffers(1, &m_LinesVertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_LINE_VERTICES * sizeof(LineVertex), nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexArrayAttrib(m_LinesVertexArray, 0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, position));
			glEnableVertexArrayAttrib(m_LinesVertexArray, 1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, color));

			for (size_t i = 0, v = 0; i < MAX_LINE_INDICES; i += 2, v += 2)
			{
				m_LinesIndices[i + 0] = v;
				m_LinesIndices[i + 1] = v + 1;
			}

			glCreateBuffers(1, &m_LinesIndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LinesIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_LinesIndices), m_LinesIndices.data(), GL_STATIC_DRAW);
		}

		m_TextureSlots.resize(TWO_D_MAX_TEXTURES);
		for (size_t i = 0; i < TWO_D_MAX_TEXTURES; i++)
		{
			m_TextureSlots[i].second = 0;
		}
		

		m_Shader = Shader::Create(vertex, pixel);

		m_TextShader = Shader::Create(L"../Dogo/resources/Shaders/freetypevertex.glsl",
			L"../Dogo/resources/Shaders/freetypepixel.glsl");

		glGenVertexArrays(1, &m_FontVertexArray);
		glGenBuffers(1, &m_FontVertexBuffer);
		glBindVertexArray(m_FontVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_FontVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * MAX_CHARACTERS, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LESS);
	}

	OpenGLRenderer2D::~OpenGLRenderer2D()
	{
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
	void OpenGLRenderer2D::DrawFrameBuffer(Quad& quad)
	{
		Submit(quad, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_QuadsBuffer), m_QuadsBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 1);
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_QuadsVertexArray);
		glDrawElements(GL_TRIANGLES, m_QuadsCount * 6, GL_UNSIGNED_INT, nullptr);
		m_QuadsCount = 0;
	}
	void OpenGLRenderer2D::Submit(Quad& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i].first == nullptr)
					continue;
				if (m_TextureSlots[i].second == (uint16_t)renderable.vertices[0].texIndex && m_TextureSlots[i].first->GetID() == tex->GetID())
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				bool available = false;
				for (size_t i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i].second == 0)
					{
						m_TextureSlots[i].second = (uint16_t)renderable.vertices[0].texIndex;
						m_TextureSlots[i].first = tex;
						available = true;
						break;
					}
				}
				if (!available)
				{
					Flush();
					m_QuadsCount = 0;
					m_TextureSlots[0].second = (uint16_t)renderable.vertices[0].texIndex;
					m_TextureSlots[0].first = tex;
				}
			}
		}
		if (m_QuadsCount >= MAX_QUADS)
		{
			Flush();
			m_QuadsCount = 0;
		}
		for(int i = 0; i < 4; i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_QuadsBuffer[m_QuadsCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(Triangle& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i].first == nullptr)
					continue;
				if (m_TextureSlots[i].second == (uint16_t)renderable.vertices[0].texIndex && m_TextureSlots[i].first->GetID() == tex->GetID())
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				bool available = false;
				for (size_t i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i].second == 0)
					{
						m_TextureSlots[i].second = (uint16_t)renderable.vertices[0].texIndex;
						m_TextureSlots[i].first = tex;
						available = true;
						break;
					}
				}
				if (!available)
				{
					Flush();
					m_QuadsCount = 0;
					m_TextureSlots[0].second = (uint16_t)renderable.vertices[0].texIndex;
					m_TextureSlots[0].first = tex;
				}
			}
		}
		if (m_TrianglesCount >= MAX_TRIANGLES)
		{
			Flush();
			m_TrianglesCount = 0;
		}
		for (int i = 0; i < 3; i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_TrianglesBuffer[m_TrianglesCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(Circle& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i].first == nullptr)
					continue;
				if (m_TextureSlots[i].second == (uint16_t)renderable.vertices[0].texIndex && m_TextureSlots[i].first->GetID() == tex->GetID())
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				bool available = false;
				for (size_t i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i].second == 0)
					{
						m_TextureSlots[i].second = (uint16_t)renderable.vertices[0].texIndex;
						m_TextureSlots[i].first = tex;
						available = true;
						break;
					}
				}
				if (!available)
				{
					Flush();
					m_QuadsCount = 0;
					m_TextureSlots[0].second = (uint16_t)renderable.vertices[0].texIndex;
					m_TextureSlots[0].first = tex;
				}
			}
		}
		if (m_CirclesCount >= MAX_CIRCLES)
		{
			Flush();
			m_CirclesCount = 0;
		}
		for (int i = 0; i < (CIRCLE_SEGMENTS + 2); i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_CirclesBuffer[m_CirclesCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(RoundedRect& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i].first == nullptr)
					continue;
				if (m_TextureSlots[i].second == (uint16_t)renderable.vertices[0].texIndex && m_TextureSlots[i].first->GetID() == tex->GetID())
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				bool available = false;
				for (size_t i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i].second == 0)
					{
						m_TextureSlots[i].second = (uint16_t)renderable.vertices[0].texIndex;
						m_TextureSlots[i].first = tex;
						available = true;
						break;
					}
				}
				if (!available)
				{
					Flush();
					m_QuadsCount = 0;
					m_TextureSlots[0].second = (uint16_t)renderable.vertices[0].texIndex;
					m_TextureSlots[0].first = tex;
				}
			}
		}
		if (m_RoundedRectsCount >= MAX_ROUNDED_RECTS)
		{
			Flush();
			m_RoundedRectsCount = 0;
		}
		int numVertices = 1 + 4 * (ROUNDED_RECT_SEGMENTS + 1);
		for (int i = 0; i < numVertices; i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_RoundedRectsBuffer[m_RoundedRectsCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(ThickLine& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i].first == nullptr)
					continue;
				if (m_TextureSlots[i].second == (uint16_t)renderable.vertices[0].texIndex && m_TextureSlots[i].first->GetID() == tex->GetID())
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				bool available = false;
				for (size_t i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i].second == 0)
					{
						m_TextureSlots[i].second = (uint16_t)renderable.vertices[0].texIndex;
						m_TextureSlots[i].first = tex;
						available = true;
						break;
					}
				}
				if (!available)
				{
					Flush();
					m_QuadsCount = 0;
					m_TextureSlots[0].second = (uint16_t)renderable.vertices[0].texIndex;
					m_TextureSlots[0].first = tex;
				}
			}
		}
		if (m_ThickLinesCount >= MAX_THICK_LINES)
		{
			Flush();
			m_ThickLinesCount = 0;
		}
		for (int i = 0; i < 4; i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_ThickLinesBuffer[m_ThickLinesCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(Line2D& renderable)
	{
		if (m_LinesCount >= MAX_LINES)
		{
			Flush();
			m_LinesCount = 0;
		}
		for (int i = 0; i < 2; i++)
			renderable.vertices[i].position = glm::vec3(*m_TransformBack * glm::vec4(renderable.vertices[i].position, 1.0f));
		m_LinesBuffer[m_LinesCount++] = renderable;
	}
	void OpenGLRenderer2D::Flush()
	{
		glDepthFunc(GL_LESS);
		QuadsFlush();
		TrianglesFlush();
		CirclesFlush();
		RoundedRectFlush();
		ThickLineFlush();
		LinesFlush();
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			m_TextureSlots[i].second = 0;
			m_TextureSlots[i].first = nullptr;
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

		// Create atlas texture
		GLuint atlasTex;
		glGenTextures(1, &atlasTex);
		glBindTexture(GL_TEXTURE_2D, atlasTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1024, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Pack glyphs
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
			float v0 = (float)(yOffset + face->glyph->bitmap.rows) / (float)atlasHeight; // bottom
			float u1 = (float)(xOffset + face->glyph->bitmap.width) / 1024.0f;
			float v1 = (float)yOffset / (float)atlasHeight; // top

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
		cmd.transform = *m_TransformBack; // capture transform stack at submission time
		m_TextCommands.push_back(cmd);
	}

	void OpenGLRenderer2D::RenderText()
	{
		if (m_TextCommands.empty()) return;

		glDepthFunc(GL_ALWAYS);
		m_TextShader->Bind();
		m_TextShader->SetUniformMatrix4f("projection", m_Proj);
		m_TextShader->SetUniform1i("text", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_FontAtlasTextureID);
		glBindVertexArray(m_FontVertexArray);

		// Temp vertex storage for the whole batch
		std::vector<float> vertices;
		vertices.reserve(m_TextCommands.size() * 6 * 4 * 16); // max estimate

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

				float xpos = cursorX + ch.bearing.x * cmd.scale;
				float ypos = cursorY + (Characters['H'].bearing.y - ch.bearing.y) * cmd.scale;

				float w = ch.size.x * cmd.scale;
				float h = ch.size.y * cmd.scale;

				float u0 = ch.uvTopLeft.x;
				float v0 = ch.uvTopLeft.y;
				float u1 = ch.uvBottomRight.x;
				float v1 = ch.uvBottomRight.y;

				float quad[6][4] = {
					{ xpos,     ypos + h, u0, v0 }, // flipped v0/v1
					{ xpos + w, ypos,     u1, v1 },
					{ xpos,     ypos,     u0, v1 },

					{ xpos,     ypos + h, u0, v0 },
					{ xpos + w, ypos + h, u1, v0 },
					{ xpos + w, ypos,     u1, v1 }
				};



				vertices.insert(vertices.end(), &quad[0][0], &quad[0][0] + 6 * 4);
				cursorX += (ch.advance >> 6) * cmd.scale;
			}

			m_TextShader->SetUniform3f("textColor", cmd.color); // color per command
			glBindBuffer(GL_ARRAY_BUFFER, m_FontVertexBuffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 4));
			vertices.clear();
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_TextCommands.clear();
	}
	void OpenGLRenderer2D::LinesFlush()
	{
		glLineWidth(5.0f);

		glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_LinesBuffer), m_LinesBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		glBindVertexArray(m_LinesVertexArray);
		glDrawElements(GL_LINES, m_LinesCount * 2, GL_UNSIGNED_INT, nullptr);
		m_LinesCount = 0;
	}
	void OpenGLRenderer2D::QuadsFlush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadsVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_QuadsBuffer), m_QuadsBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0 && m_TextureSlots[i].first != nullptr)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_QuadsVertexArray);
		glDrawElements(GL_TRIANGLES, m_QuadsCount * 6, GL_UNSIGNED_INT, nullptr);
		m_QuadsCount = 0;
	}
	void OpenGLRenderer2D::TrianglesFlush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_TrianglesBuffer), m_TrianglesBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0 && m_TextureSlots[i].first != nullptr)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_TrianglesVertexArray);
		glDrawElements(GL_TRIANGLES, m_TrianglesCount * 3, GL_UNSIGNED_INT, nullptr);
		m_TrianglesCount = 0;
	}
	void OpenGLRenderer2D::CirclesFlush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_CirclesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_CirclesBuffer), m_CirclesBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0 && m_TextureSlots[i].first != nullptr)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_CirclesVertexArray);
		glDrawElements(GL_TRIANGLES, m_CirclesCount * CIRCLE_SEGMENTS * 3, GL_UNSIGNED_INT, nullptr);
		m_CirclesCount = 0;
	}
	void OpenGLRenderer2D::RoundedRectFlush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RoundedRectVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_RoundedRectsBuffer), m_RoundedRectsBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0 && m_TextureSlots[i].first != nullptr)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_RoundedRectVertexArray);
		glDrawElements(GL_TRIANGLES, m_RoundedRectsCount * ROUNDED_RECT_SEGMENTS * 4 * 3, GL_UNSIGNED_INT, nullptr);
		m_RoundedRectsCount = 0;
	}
	void OpenGLRenderer2D::ThickLineFlush()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ThickLineVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_ThickLinesBuffer), m_ThickLinesBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0 && m_TextureSlots[i].first != nullptr)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_ThickLineVertexArray);
		glDrawElements(GL_TRIANGLES, m_ThickLinesCount * 6, GL_UNSIGNED_INT, nullptr);
		m_ThickLinesCount = 0;
	}
}