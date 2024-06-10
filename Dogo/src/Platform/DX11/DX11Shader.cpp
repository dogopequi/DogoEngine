#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11Shader.h"
#include "Dogo/Logger.h"
#include "Graphics/WindowsWindow.h"

namespace Dogo
{
	DX11Shader* DX11Shader::Create(const std::wstring& filepath, ShaderType type)
	{
		switch (type)
		{
		case ShaderType::None:
			DG_ERROR("Shader type doesn't exist");
			return nullptr;
			break;
		case ShaderType::COMPUTE:
			return new DX11ComputeShader(filepath);
			break;
		case ShaderType::VERTEX:
			return new DX11VertexShader(filepath);
			break;
		case ShaderType::FRAGMENT:
			return new DX11PixelShader(filepath);
			break;
		case ShaderType::GEOMETRY:
			return new DX11GeometryShader(filepath);
			break;
		default:
			DG_ERROR("Shader type doesn't exist");
			return nullptr;
			break;
		}
	}
	void DX11Shader::SetUniform1i(const std::string& name, int32_t value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(int32_t);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		int32_t* dataPtr = (int32_t*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(int32_t));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform2i(const std::string& name, glm::ivec2 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::ivec2);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::ivec2* dataPtr = (glm::ivec2*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::ivec2));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);
		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform3i(const std::string& name, glm::ivec3 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::ivec3);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::ivec3* dataPtr = (glm::ivec3*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::ivec3));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform4i(const std::string& name, glm::ivec4 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::ivec4);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::ivec4* dataPtr = (glm::ivec4*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::ivec4));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniformBool(const std::string& name, bool value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(bool);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		bool* dataPtr = (bool*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(bool));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);
		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform1f(const std::string& name, float value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(float);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		float* dataPtr = (float*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(float));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform2f(const std::string& name, glm::vec2 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::vec2);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::vec2* dataPtr = (glm::vec2*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::vec2));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform3f(const std::string& name, glm::vec3 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::vec3);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::vec3* dataPtr = (glm::vec3*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::vec3));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniform4f(const std::string& name, glm::vec4 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::vec4);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::vec4* dataPtr = (glm::vec4*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::vec4));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniformMatrix3f(const std::string& name, glm::mat3 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::mat3);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::mat3* dataPtr = (glm::mat3*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::mat3));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);

		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	void DX11Shader::SetUniformMatrix4f(const std::string& name, glm::mat4 value, uint8_t index)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		ZeroMemory(&matrixBufferDesc, sizeof(matrixBufferDesc));
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(glm::mat4);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		HRESULT result = DX11Context::GetContext()->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, &m_Buffer);
		if (FAILED(result))
		{
			DG_ERROR("Failed to create buffer");
		}
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		result = DX11Context::GetContext()->GetDeviceContext()->Map(m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			DG_ERROR("Failed to map");
		}
		glm::mat4* dataPtr = (glm::mat4*)mappedResource.pData;
		CopyMemory(mappedResource.pData, &value, sizeof(glm::mat4));
		DX11Context::GetContext()->GetDeviceContext()->Unmap(m_Buffer, 0);
		DX11Context::GetContext()->GetDeviceContext()->VSSetConstantBuffers(index, 1, &m_Buffer);
	}
	DX11VertexShader::DX11VertexShader(const std::wstring& filepath)
	{
		D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, "main", "vs_5_0", 0, 0, m_Blob.GetAddressOf(), nullptr);
		DX11Context::GetContext()->GetDevice().Get()->CreateVertexShader(m_Blob.Get()->GetBufferPointer(), m_Blob.Get()->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());

	}
	DX11VertexShader::~DX11VertexShader()
	{
		m_VertexShader.Reset();
		m_Blob.Reset();
	}
	void DX11VertexShader::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->VSSetShader(m_VertexShader.Get(), nullptr, NULL);
	}
	void DX11VertexShader::Unbind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->VSSetShader(nullptr, nullptr, NULL);
	}
	DX11PixelShader::DX11PixelShader(const std::wstring& filepath)
	{
		D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, "main", "ps_5_0", 0, 0, m_Blob.GetAddressOf(), nullptr);
		DX11Context::GetContext()->GetDevice().Get()->CreatePixelShader(m_Blob.Get()->GetBufferPointer(), m_Blob.Get()->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf());
	}
	DX11PixelShader::~DX11PixelShader()
	{
		m_PixelShader.Reset();
		m_Blob.Reset();
	}
	void DX11PixelShader::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetShader(m_PixelShader.Get(), nullptr, NULL);
	}
	void DX11PixelShader::Unbind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetShader(nullptr, nullptr, NULL);
	}
	DX11GeometryShader::DX11GeometryShader(const std::wstring& filepath)
	{

		D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, "main", "gs_5_0", 0, 0, m_Blob.GetAddressOf(), nullptr);
		DX11Context::GetContext()->GetDevice().Get()->CreateGeometryShader(m_Blob.Get()->GetBufferPointer(), m_Blob.Get()->GetBufferSize(), nullptr, m_GeometryShader.GetAddressOf());
	}
	DX11GeometryShader::~DX11GeometryShader()
	{
		m_GeometryShader.Reset();
		m_Blob.Reset();
	}
	void DX11GeometryShader::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->GSSetShader(m_GeometryShader.Get(), nullptr, NULL);
	}
	void DX11GeometryShader::Unbind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->GSSetShader(nullptr, nullptr, NULL);
	}
	DX11ComputeShader::DX11ComputeShader(const std::wstring& filepath)
	{

		D3DCompileFromFile(filepath.c_str(), nullptr, nullptr, "main", "cs_5_0", 0, 0, m_Blob.GetAddressOf(), nullptr);
		DX11Context::GetContext()->GetDevice().Get()->CreateComputeShader(m_Blob.Get()->GetBufferPointer(), m_Blob.Get()->GetBufferSize(), nullptr, m_ComputeShader.GetAddressOf());
	}
	DX11ComputeShader::~DX11ComputeShader()
	{
		m_ComputeShader.Reset();
		m_Blob.Reset();
	}
	void DX11ComputeShader::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->CSSetShader(m_ComputeShader.Get(), nullptr, NULL);
	}
	void DX11ComputeShader::Unbind()
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->GSSetShader(nullptr, nullptr, NULL);
	}
}

#endif