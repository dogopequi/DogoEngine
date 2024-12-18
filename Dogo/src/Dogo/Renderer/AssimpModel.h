#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include "VertexHash.h"
#include "Shader.h"
#include "Buffers.h"
#include "Graphics/GraphicsContext.h"
#include "Texture.h"
#include "Platform/DX11/DX11VertexBuffer.h"
#include "Platform/DX11/DX11Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Dogo
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<BufferLayout> layout, const std::shared_ptr<Shader>& vertex, const std::shared_ptr<Shader>& pixel, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture*>& textures);
        ~Mesh() {}

#if DG_PLATFORM_WINDOWS
        inline void SetLayout(std::shared_ptr<Shader> shader) const
        {
            std::shared_ptr<DX11VertexShader> dx11shader = std::static_pointer_cast<DX11VertexShader>(shader);
            std::shared_ptr<DX11VertexBuffer> dx11vbo = std::static_pointer_cast<DX11VertexBuffer>(m_VertexBuffer);
            dx11vbo->SetLayout(*m_Layout, dx11shader->GetBufferPointer(), dx11shader->GetBufferLength());
        }
#endif
        inline void SetLayout() const { m_VertexBuffer->SetLayout(*m_Layout); }


        void Draw() const;


        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }


        inline std::shared_ptr<VertexArray> GetVAO() const { return m_VertexArray; }
        inline std::shared_ptr<VertexBuffer> GetVBO() const { return m_VertexBuffer; }
        inline std::shared_ptr<IndexBuffer> GetIBO() const { return m_IndexBuffer; }

    private:


        std::vector<Vertex> m_Vertices{};

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<BufferLayout> m_Layout;
        std::shared_ptr<Shader> m_VertexShader;
        std::shared_ptr<Shader> m_PixelShader;

        std::vector<std::shared_ptr<Texture>> m_Textures;
        std::vector<uint32_t> m_Indices{};

    };


    class Model
    {
    public:
        Model(const std::string& path, const glm::vec3 pos, BufferLayout& layout, const std::wstring& vertex, const std::wstring& pixel/*, const std::vector<Texture*>& textures*/);

        void Draw() const;

        inline glm::vec3 GetPosition() const { return m_Position; }
        inline void SetPosition(const glm::vec3& pos) { m_Position = pos; }
        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }

        ~Model(){}

    private:
        void LoadModel(const std::string& path);

        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& name);

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


        std::vector<Mesh> m_Meshes;
        std::string m_Directory;

        std::vector<Texture*> m_TexturesLoaded;

        std::shared_ptr<Shader> m_VertexShader;
        std::shared_ptr<Shader> m_PixelShader;
        std::shared_ptr<BufferLayout> m_Layout;
        glm::vec3 m_Position;

    };
}
