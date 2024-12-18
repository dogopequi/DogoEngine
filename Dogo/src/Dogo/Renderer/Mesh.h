#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include "VertexHash.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"

namespace Dogo
{
    struct Material1
    {
        std::shared_ptr<Texture> diffuse;
        std::shared_ptr<Texture> specular;
        std::shared_ptr<Texture> emission;
        float shininess;
    };

	class OldMesh
	{
	public:
        OldMesh(const std::string& inputfile, const glm::vec3 pos, BufferLayout& layout, const std::wstring& vertex, const std::wstring& pixel) : m_Position(pos)
		{
            LoadFromFile(inputfile);

            SetVertexAndPixelShader(vertex, pixel);
            m_Layout = std::make_shared<BufferLayout>(layout);
            m_VertexArray.reset(VertexArray::Create());
            m_VertexArray->Bind();
            std::vector<float> vertexData;
            for (const auto& vertex : vertices) {
                vertexData.push_back(vertex.vertices.x);
                vertexData.push_back(vertex.vertices.y);
                vertexData.push_back(vertex.vertices.z);
                vertexData.push_back(vertex.normals.x);
                vertexData.push_back(vertex.normals.y);
                vertexData.push_back(vertex.normals.z);
                vertexData.push_back(vertex.texCoords.x);
                vertexData.push_back(vertex.texCoords.y);
            }
            m_VertexBuffer.reset(VertexBuffer::Create(vertices.size() * sizeof(Vertex) , sizeof(Vertex), vertexData.data()));
            m_IndexBuffer.reset(IndexBuffer::Create(indices.size() * sizeof(uint32_t), indices.data(), indices.size()));
            m_VertexBuffer->Bind();
            m_IndexBuffer->Bind();
            RenderAPI api = GraphicsContext::Get()->GetAPI();
            switch (api)
            {
            case RenderAPI::OpenGL:
            {
                SetLayout();
            }break;
#if DG_PLATFORM_WINDOWS
            case RenderAPI::D3D11:
            {
                SetLayout(m_VertexShader);
            }
#endif
            break;
            default:
                DG_FATAL("API NOT SPECIFIED");
            }
            m_VertexArray->AddBuffer(m_VertexBuffer);
		}
		~OldMesh(){}

        inline glm::vec3 GetPosition() const { return m_Position; }

        inline void SetVertexAndPixelShader(const std::wstring& vertex, const std::wstring& pixel)
        {
            RenderAPI api = GraphicsContext::GetAPI();
            switch (api)
            {
            case RenderAPI::API_NONE:
                DG_FATAL("Invalid render API");
                break;
            case RenderAPI::OpenGL:
                m_VertexShader.reset(Shader::Create(vertex, pixel));
                m_PixelShader = m_VertexShader;
                break;
            case RenderAPI::D3D11:
                m_VertexShader.reset(Shader::Create(vertex, ShaderType::VERTEX));
                m_PixelShader.reset(Shader::Create(pixel, ShaderType::FRAGMENT));
                break;
            case RenderAPI::D3D12:
                DG_FATAL("Not implemented");
                break;
            case RenderAPI::VULKAN:
                DG_FATAL("Not implemented");
                break;
            default:
            {
                DG_FATAL("Invalid render API, defaulted to OPENGL SPEC");
            }
            break;
            }
        }
#if DG_PLATFORM_WINDOWS
        inline void SetLayout(std::shared_ptr<Shader> shader) const
        {
            std::shared_ptr<DX11VertexShader> dx11shader = std::static_pointer_cast<DX11VertexShader>(shader);
            std::shared_ptr<DX11VertexBuffer> dx11vbo = std::static_pointer_cast<DX11VertexBuffer>(m_VertexBuffer);
            dx11vbo->SetLayout(*m_Layout, dx11shader->GetBufferPointer(), dx11shader->GetBufferLength());
        }
#endif
        inline void SetLayout() const { m_VertexBuffer->SetLayout(*m_Layout); }
        void LoadFromFile(const std::string& inputfile)
        {
            tinyobj::ObjReaderConfig reader_config;
            tinyobj::ObjReader reader;

            if (!reader.ParseFromFile(inputfile, reader_config)) {
                if (!reader.Error().empty()) {
                    std::cerr << "TinyObjReader: " << reader.Error();
                }
                exit(1);
            }
            if (!reader.Warning().empty()) {
                std::cout << "TinyObjReader: " << reader.Warning();
            }

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str())) {
                throw std::runtime_error(warn + err);
            }

            std::unordered_map<Vertex, uint32_t> uniqueVertices{};

            for (const auto& shape : shapes) 
            {
                for (const auto& index : shape.mesh.indices) {
                    Vertex vertex{};

                    // Check if vertex index is valid
                    if (index.vertex_index >= 0) {
                        vertex.vertices = {
                            attrib.vertices[3 * index.vertex_index + 0],
                            attrib.vertices[3 * index.vertex_index + 1],
                            attrib.vertices[3 * index.vertex_index + 2]
                        };
                    }

                    // Check if normal index is valid
                    if (index.normal_index >= 0) {
                        vertex.normals = {
                            attrib.normals[3 * index.normal_index + 0],
                            attrib.normals[3 * index.normal_index + 1],
                            attrib.normals[3 * index.normal_index + 2]
                        };
                    }
                    else {
                        // Handle missing normals
                        vertex.normals = glm::vec3(0.0f, 0.0f, 0.0f); // Default normal
                    }

                    // Check if texcoord index is valid
                    if (index.texcoord_index >= 0) {
                        vertex.texCoords = {
                            attrib.texcoords[2 * index.texcoord_index + 0],
                            attrib.texcoords[2 * index.texcoord_index + 1]
                        };
                    }
                    else {
                        // Handle missing texture coordinates
                        vertex.texCoords = glm::vec2(0.0f, 0.0f); // Default texture coordinates
                    }

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    indices.push_back(uniqueVertices[vertex]);
                }
            }
        }


        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }


        inline std::shared_ptr<VertexArray> GetVAO() const { return m_VertexArray; }
        inline std::shared_ptr<VertexBuffer> GetVBO() const { return m_VertexBuffer; }
        inline std::shared_ptr<IndexBuffer> GetIBO() const { return m_IndexBuffer; }

	private:

        void printIndicesToFile(const std::vector<uint32_t>& indices, const std::string& filename) {
            std::ofstream outFile(filename);

            if (!outFile) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return;
            }

            for (int j = 0; j < indices.size(); j++) {
                outFile << "Indice " << j << ": " << indices.at(j) << std::endl;
            }

            outFile.close();
        }

        void printVerticesToFile(const std::vector<Vertex>& vertices, const std::string& filename) {
            std::ofstream outFile(filename);

            if (!outFile) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return;
            }

            for (const auto& vert : vertices) {
                outFile << "VERTICES" << std::endl;
                outFile << "x: " << vert.vertices.x << ", y: " << vert.vertices.y << ", z: " << vert.vertices.z << std::endl;
                outFile << "NORMAL" << std::endl;
                outFile << "x: " << vert.normals.x << ", y: " << vert.normals.y << ", z: " << vert.normals.z << std::endl;
                outFile << "TEXCOORD" << std::endl;
                outFile << "x: " << vert.texCoords.x << ", y: " << vert.texCoords.y << std::endl;
            }

            outFile.close();
        }

        std::vector<Vertex> vertices{};

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<BufferLayout> m_Layout;
        std::shared_ptr<Shader> m_VertexShader;
        std::shared_ptr<Shader> m_PixelShader;
        Material m_Material;

        std::vector<uint32_t> indices{};

        glm::vec3 m_Position;

	};
}
