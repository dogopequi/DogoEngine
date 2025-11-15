#include "dgpch.h"
#include "Line.h"

namespace Dogo
{
	void Line::Draw() const
	{
		m_PixelShader->Bind();
		m_VertexArray->Bind();
		m_PixelShader->SetUniform3f("color", m_Color);
		m_VertexArray->DrawArrays();
	}
}