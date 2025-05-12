#include "dgpch.h"
#include "OpenGLRenderer2D.h"

namespace Dogo{
	OpenGLRenderer2D::OpenGLRenderer2D(const std::wstring& vertex, const std::wstring& pixel)
	{
		//////////QUADS
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

		////////////// LINES

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


		m_TextureSlots.resize(TWO_D_MAX_TEXTURES);
		for (size_t i = 0; i < TWO_D_MAX_TEXTURES; i++)
		{
			m_TextureSlots[i].second = 0;
		}
		

		m_Shader = Shader::Create(vertex, pixel);
	}
	OpenGLRenderer2D::~OpenGLRenderer2D()
	{
	}
	void OpenGLRenderer2D::SetViewMatrix(const glm::mat4& view)
	{
	}
	void OpenGLRenderer2D::SetProjectionMatrix(const glm::mat4& proj)
	{
	}
	void OpenGLRenderer2D::SetModelMatrix(const glm::mat4& model)
	{
	}
	void OpenGLRenderer2D::SetTransformMatrix(const glm::mat4& model)
	{
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
	void OpenGLRenderer2D::Submit(Quad& renderable, Texture* tex)
	{
		if (renderable.vertices[0].texIndex != 0.0f)
		{
			boolean found = false;
			for (size_t i = 0; i < m_TextureSlots.size(); i++)
			{
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
					for (size_t i = 0; i < m_TextureSlots.size(); i++)
					{
						m_TextureSlots[i].second = 0;
						m_TextureSlots[i].first = nullptr;
					}
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
		m_QuadsBuffer[m_QuadsCount++] = renderable;
	}
	void OpenGLRenderer2D::Submit(const Line2D& renderable)
	{
		if (m_LinesCount >= MAX_LINES)
		{
			Flush();
			m_LinesCount = 0;
		}
		m_LinesBuffer[m_LinesCount++] = renderable;
	}
	void OpenGLRenderer2D::Flush()
	{
		QuadsFlush();
		LinesFlush();
	}
	void OpenGLRenderer2D::LinesFlush()
	{
		glLineWidth(1.0f); // use before rendering lines

		glBindBuffer(GL_ARRAY_BUFFER, m_LinesVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_LinesBuffer), m_LinesBuffer.data());
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", m_View);
		m_Shader->SetUniformMatrix4f("projection", m_Proj);
		m_Shader->SetUniformMatrix4f("model", m_Model);
		m_Shader->SetUniform1i("mode", 1);
		glBindVertexArray(m_LinesVertexArray);
		DG_INFO("Lines Count: %d", m_LinesCount);
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
		m_Shader->SetUniformMatrix4f("model", m_Model);
		m_Shader->SetUniform1i("mode", 0);
		for (size_t i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i].second != 0)
			{
				m_TextureSlots[i].first->Bind(m_TextureSlots[i].second);
			}
		}
		m_Shader->SetUniform1iv("textures", m_Samplers, 16);
		glBindVertexArray(m_QuadsVertexArray);
		glDrawElements(GL_TRIANGLES, m_QuadsCount * 6, GL_UNSIGNED_INT, nullptr);
		m_QuadsCount = 0;
	}
}