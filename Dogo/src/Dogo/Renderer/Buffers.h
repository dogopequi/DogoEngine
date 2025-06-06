#pragma once
#include "Dogo/Logger.h"
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo {

	enum class ShaderDataType
	{
		TYPE_NONE, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, uInt, uInt2, uInt3, uInt4, Boolean
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::uInt:      return 4;
		case ShaderDataType::uInt2:     return 4 * 2;
		case ShaderDataType::uInt3:     return 4 * 3;
		case ShaderDataType::uInt4:     return 4 * 4;
		case ShaderDataType::Boolean:     return 1;
		}

		DG_ASSERT_MSG(false, "Unknown ShaderDataType");
		return 0;
	}

	static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::uInt:      return GL_UNSIGNED_INT;
		case ShaderDataType::uInt2:     return GL_UNSIGNED_INT;
		case ShaderDataType::uInt3:     return GL_UNSIGNED_INT;
		case ShaderDataType::uInt4:     return GL_UNSIGNED_INT;
		case ShaderDataType::Boolean:     return GL_BOOL;
		}

		DG_ASSERT_MSG(false, "Unknown ShaderDataType");
		return 0;
	}
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::uInt:     return 1;
			case ShaderDataType::uInt2:    return 2;
			case ShaderDataType::uInt3:    return 3;
			case ShaderDataType::uInt4:    return 4;
			case ShaderDataType::Boolean:    return 1;
			}

			DG_ASSERT_MSG(false, "Unknown ShaderDataType");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(uint32_t bufferSize, uint32_t componentSize, float* data);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual inline uint32_t getSize() const = 0;
		virtual inline uint32_t getComponentCount() const = 0;

		static IndexBuffer* Create(uint32_t size, uint32_t* data, uint32_t count);
	};

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddBuffer(std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void Draw(uint32_t count) = 0;
		virtual void DrawArrays() = 0;

		static VertexArray* Create();
	};
}