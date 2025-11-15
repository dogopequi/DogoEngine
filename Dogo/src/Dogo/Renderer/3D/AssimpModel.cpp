#include "dgpch.h"
#include "AssimpModel.h"

namespace Dogo
{
        Mesh::Mesh(const std::shared_ptr<BufferLayout> layout, const std::shared_ptr<Shader>& vertex, const std::shared_ptr<Shader>& pixel, const std::vector<assimpVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture*>& textures) : m_VertexShader(vertex), m_PixelShader(pixel), m_Indices(indices), m_Vertices(vertices)
        {
            m_Layout = layout;
            m_VertexArray.reset(VertexArray::Create());
            m_VertexArray->Bind();
            std::vector<float> vertexData;
            for (const auto& vertex : m_Vertices) {
                vertexData.push_back(vertex.vertices.x);
                vertexData.push_back(vertex.vertices.y);
                vertexData.push_back(vertex.vertices.z);
                vertexData.push_back(vertex.normals.x);
                vertexData.push_back(vertex.normals.y);
                vertexData.push_back(vertex.normals.z);
                vertexData.push_back(vertex.texCoords.x);
                vertexData.push_back(vertex.texCoords.y);
            }
            m_VertexBuffer.reset(VertexBuffer::Create(static_cast<uint32_t>(m_Vertices.size() * sizeof(assimpVertex)), static_cast<uint32_t>(sizeof(assimpVertex)), vertexData.data()));
            m_IndexBuffer.reset(IndexBuffer::Create(static_cast<uint32_t>(m_Indices.size() * sizeof(uint32_t)), m_Indices.data(), static_cast<uint32_t>(m_Indices.size())));
            m_VertexBuffer->Bind();
            m_IndexBuffer->Bind();
            RenderAPI api = GraphicsContext::Get()->GetAPI();
            switch (api)
            {
            case RenderAPI::OpenGL:
            {
                SetLayout();
            }break;
            default:
                DG_FATAL("API NOT SPECIFIED");
            }
            m_VertexArray->AddBuffer(m_VertexBuffer);
            m_Textures.resize(textures.size());
            for (int i = 0; i < textures.size(); i++)
            {
                m_Textures[i].reset(TextureManager::Create(textures[i]->GetFilePath(), TextureType::T_2D, FilterMode::BILINEAR, Wrapping::CLAMP_TO_EDGE, true));
            }
        }


        void Mesh::Draw() const
        {
            m_PixelShader->Bind();
            m_VertexArray->Bind();
            uint32_t diffuseNr = 1;
            uint32_t specularNr = 1;
            uint32_t normalNr = 1;
            uint32_t heightNr = 1;
            for (uint32_t i = 0; i < m_Textures.size(); i++)
            {
                // BROKEN
                //std::string number;
                //ImageType name = m_Textures[i]->GetType();
                //if (name == "texture_diffuse")
                //    number = std::to_string(diffuseNr++);
                //else if (name == "texture_specular")
                //    number = std::to_string(specularNr++);
                //else if (name == "texture_normal")
                //    number = std::to_string(normalNr++);
                //else if (name == "texture_height")
                //    number = std::to_string(heightNr++);

                //std::string test = ((name + number).c_str());
                //m_PixelShader->SetUniform1i((name + number).c_str(), i);
                //m_Textures[i]->Bind(i);
            }
            glActiveTexture(GL_TEXTURE0);

            m_VertexArray->Draw(m_IndexBuffer->getComponentCount());
        }

        Model::Model(const std::string& path, BufferLayout& layout, const std::wstring& vertex, const std::wstring& pixel/*, const std::vector<Texture*>& textures*/)
        {
            m_Layout = std::make_shared<BufferLayout>(layout);
            SetVertexAndPixelShader(vertex, pixel);
            LoadModel(path);
        }
        Model::~Model()
        {
        }
        void Model::Draw() const
        {
            for (int i = 0; i < m_Meshes.size(); i++)
            {
                m_Meshes[i].Draw();
            }
        }

        void Model::LoadModel(const std::string& path)
        {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                DG_ERROR("ERROR::ASSIMP::%s", importer.GetErrorString());
                return;
            }
            m_Directory = path.substr(0, path.find_last_of('/'));

            ProcessNode(scene->mRootNode, scene);
        }

        void Model::ProcessNode(aiNode* node, const aiScene* scene)
        {
            for (uint32_t i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                m_Meshes.push_back(ProcessMesh(mesh, scene));
            }

            for (uint32_t i = 0; i < node->mNumChildren; i++)
            {
                ProcessNode(node->mChildren[i], scene);
            }

        }
        Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
        {
            std::vector<assimpVertex> vertices;
            std::vector<uint32_t> indices;
            std::vector<Texture*> textures;

            for (uint32_t i = 0; i < mesh->mNumVertices; i++)
            {
                assimpVertex vertex;
                glm::vec3 vectorV;
                vectorV.x = mesh->mVertices[i].x;
                vectorV.y = mesh->mVertices[i].y;
                vectorV.z = mesh->mVertices[i].z;
                vertex.vertices = vectorV;

                if (mesh->HasNormals())
                {

                    glm::vec3 vectorN;
                    vectorN.x = mesh->mNormals[i].x;
                    vectorN.y = mesh->mNormals[i].y;
                    vectorN.z = mesh->mNormals[i].z;
                    vertex.normals = vectorN;
                }
                if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    glm::vec2 vec;
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.texCoords = vec;
                }
                else
                {
                    vertex.texCoords = glm::vec2(0.0f, 0.0f);
                }
                vertices.push_back(vertex);
            }
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
            if (mesh->mMaterialIndex >= 0)
            {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

                std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

                std::vector<Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
                textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

                std::vector<Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
                textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
            }

            return Mesh(m_Layout, m_VertexShader, m_PixelShader, vertices, indices, textures);

        }
        std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& name)
        {
            std::vector<Texture*> textures;
            for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
            {
                aiString str;
                material->GetTexture(type, i, &str);
                bool skip = false;
                for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++)
                {
                    if (std::strcmp(m_TexturesLoaded[j]->GetFilePath().data(), str.C_Str()) == 0)
                    {
                        textures.push_back(m_TexturesLoaded[j]);
                        skip = true;
                        break;
                    }
                }
                if (!skip)
                {
                    Texture* texture = TextureManager::Create((m_Directory + "/" + str.C_Str()), TextureType::T_2D, FilterMode::BILINEAR, Wrapping::CLAMP_TO_EDGE, true);
                    textures.push_back(texture);
                    m_TexturesLoaded.push_back(texture);
                }
            }
            return textures;
        }
}