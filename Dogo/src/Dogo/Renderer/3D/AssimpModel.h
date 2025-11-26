#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include "Dogo/Renderer/Core/VertexHash.h"
#include "Dogo/Renderer/Core/Shader.h"
#include "Dogo/Renderer/Core/Buffers.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Renderer/Core/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace Dogo
{
    class Mesh
    {
    public:
        Mesh(const std::shared_ptr<BufferLayout> layout, const std::shared_ptr<Shader>& vertex, const std::shared_ptr<Shader>& pixel, const std::vector<assimpVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<std::shared_ptr<Texture>>& textures);
        ~Mesh() {}

        inline void SetLayout() const { m_VertexBuffer->SetLayout(*m_Layout); }


        void Draw() const;


        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }


        inline std::shared_ptr<VertexArray> GetVAO() const { return m_VertexArray; }
        inline std::shared_ptr<VertexBuffer> GetVBO() const { return m_VertexBuffer; }
        inline std::shared_ptr<IndexBuffer> GetIBO() const { return m_IndexBuffer; }

    private:


        std::vector<assimpVertex> m_Vertices{};

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
        Model(const std::string& path, BufferLayout& layout, const std::wstring& vertex, const std::wstring& pixel/*, const std::vector<Texture*>& textures*/);

        void Draw() const;

        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }
        ~Model();

    private:
        void LoadModel(const std::string& path);

        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& name);
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

        std::vector<std::shared_ptr<Texture>> m_TexturesLoaded;

        std::shared_ptr<Shader> m_VertexShader;
        std::shared_ptr<Shader> m_PixelShader;
        std::shared_ptr<BufferLayout> m_Layout;
    };
}
