#pragma once
#if DG_PLATFORM_WINDOWS
#include "Dogo/Core.h"
#include "Dogo/Renderer/Shader.h"
#include "Platform/DX11/DX11Context.h"
namespace Dogo
{
	using namespace DirectX;
	using namespace PackedVector;
	using Microsoft::WRL::ComPtr;
	class DX11Shader : public Shader
	{
	public:

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const void* GetBufferPointer() const = 0;
		virtual SIZE_T GetBufferLength() const = 0;

		static DX11Shader* Create(const std::wstring& filepath, ShaderType type);

		void SetUniform1i(const std::string& name, int32_t value, uint8_t index = 0) override;
		void SetUniform2i(const std::string& name, glm::ivec2 value, uint8_t index = 0) override;
		void SetUniform3i(const std::string& name, glm::ivec3 value, uint8_t index = 0) override;
		void SetUniform4i(const std::string& name, glm::ivec4 value, uint8_t index = 0) override;

		void SetUniformBool(const std::string& name, bool value, uint8_t index = 0) override;

		void SetUniform1f(const std::string& name, float value, uint8_t index = 0) override;
		void SetUniform2f(const std::string& name, glm::vec2 value, uint8_t index = 0) override;
		void SetUniform3f(const std::string& name, glm::vec3 value, uint8_t index = 0) override;
		void SetUniform4f(const std::string& name, glm::vec4 value, uint8_t index = 0) override;

		void SetUniformMatrix3f(const std::string& name, glm::mat3 value, uint8_t index = 0) override;
		void SetUniformMatrix4f(const std::string& name, glm::mat4 value, uint8_t index = 0) override;

	protected:
		ID3D11Buffer* m_Buffer = nullptr;
	};

	class DX11VertexShader : public DX11Shader
	{
	public:
		DX11VertexShader(const std::wstring& filepath);
		~DX11VertexShader();

		virtual const void* GetBufferPointer() const override { return m_Blob.Get()->GetBufferPointer(); }
		virtual SIZE_T GetBufferLength() const override { return m_Blob.Get()->GetBufferSize(); }

		void Bind() override;
		void Unbind() override;

	private:
		ComPtr<ID3DBlob> m_Blob;
		ComPtr<ID3D11VertexShader> m_VertexShader;
	};

	class DX11PixelShader : public DX11Shader
	{
	public:
		DX11PixelShader(const std::wstring& filepath);
		~DX11PixelShader();

		virtual const void* GetBufferPointer() const override { return m_Blob.Get()->GetBufferPointer(); }
		virtual SIZE_T GetBufferLength() const override { return m_Blob.Get()->GetBufferSize(); }

		void Bind() override;
		void Unbind() override;

	private:
		ComPtr<ID3DBlob> m_Blob;
		ComPtr<ID3D11PixelShader> m_PixelShader;
	};

	class DX11GeometryShader : public DX11Shader
	{
	public:
		DX11GeometryShader(const std::wstring& filepath);
		~DX11GeometryShader();

		virtual const void* GetBufferPointer() const override { return m_Blob.Get()->GetBufferPointer(); }
		virtual SIZE_T GetBufferLength() const override { return m_Blob.Get()->GetBufferSize(); }

		void Bind() override;
		void Unbind() override;

	private:
		ComPtr<ID3DBlob> m_Blob;
		ComPtr<ID3D11GeometryShader> m_GeometryShader;
	};

	class DX11ComputeShader : public DX11Shader
	{
	public:
		DX11ComputeShader(const std::wstring& filepath);
		~DX11ComputeShader();

		virtual const void* GetBufferPointer() const override { return m_Blob.Get()->GetBufferPointer(); }
		virtual SIZE_T GetBufferLength() const override { return m_Blob.Get()->GetBufferSize(); }

		void Bind() override;
		void Unbind() override;

	private:
		ComPtr<ID3DBlob> m_Blob;
		ComPtr<ID3D11ComputeShader> m_ComputeShader;
	};
}
#endif

