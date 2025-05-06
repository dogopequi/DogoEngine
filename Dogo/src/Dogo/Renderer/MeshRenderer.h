#pragma once

#include "Mesh.h"
#include "Dogo/Core.h"
namespace Dogo
{
	struct Light1 {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	struct MatrixPass1
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 transform;
	};
	class MeshRenderer
	{
	public:
		MeshRenderer()
		{
			MVP = std::make_unique<MatrixPass1>();
			MVP->model = glm::mat4(1.0f);
			MVP->view = glm::mat4(1.0f);
			MVP->projection = glm::mat4(1.0f);
			MVP->transform = glm::mat4(1.0f);
			RenderAPI api = GraphicsContext::GetAPI();
			if (api == RenderAPI::OpenGL)
				glEnable(GL_DEPTH_TEST);
		}
		~MeshRenderer(){}

		void Submit(const OldMesh& renderable)
		{
			m_RenderQueue.push_back(&renderable);
		}
		void Flush()
		{
			while (!m_RenderQueue.empty())
			{
				const OldMesh* renderable = m_RenderQueue.front();
				RenderAPI api = GraphicsContext::GetAPI();
				{
					switch (api)
					{
					case Dogo::RenderAPI::API_NONE:
						DG_FATAL("No API specified");
						break;
					case Dogo::RenderAPI::OpenGL:
						renderable->GetVertexShader()->Bind();
						break;
					case Dogo::RenderAPI::VULKAN:
						DG_FATAL("Not Implemented");
						break;
					default:
						DG_FATAL("No API specified");
						break;
					}
				}
				{
					renderable->GetVertexShader()->SetUniformMatrix4f("view", MVP->view, 1);
					renderable->GetVertexShader()->SetUniformMatrix4f("projection", MVP->projection, 2);
					//renderable->GetPixelShader()->SetUniform3f("objcolor", renderable->GetColor());
					//renderable->GetPixelShader()->SetUniform3f("viewPos", m_ViewPos);
					//if (renderable->GetMaterial().diffuse != nullptr)
					//{
					//	renderable->GetMaterial().diffuse->Bind(0, "material.diffuse");
					//	renderable->GetPixelShader()->SetUniform1i("material.diffuse", 0);
					//}
					//if (renderable->GetMaterial().specular != nullptr)
					//{
					//	renderable->GetMaterial().specular->Bind(1, "material.specular");
					//	renderable->GetPixelShader()->SetUniform1i("material.specular", 1);
					//}
					//if (renderable->GetMaterial().emission != nullptr)
					//{
					//	renderable->GetMaterial().emission->Bind(2, "material.emission");
					//	renderable->GetPixelShader()->SetUniform1i("material.emission", 2);
					//}
					//renderable->GetPixelShader()->SetUniform1f("material.shininess", renderable->GetMaterial().shininess);

					//renderable->GetPixelShader()->SetUniform3f("light.position", m_Light.position);
					//renderable->GetPixelShader()->SetUniform3f("light.ambient", m_Light.ambient);
					//renderable->GetPixelShader()->SetUniform3f("light.diffuse", m_Light.diffuse);
					//renderable->GetPixelShader()->SetUniform3f("light.specular", m_Light.specular);
				}

				renderable->GetVAO()->Bind();
				MVP->transform = glm::mat4(1.0f);
				MVP->transform = glm::translate(MVP->transform, renderable->GetPosition());
				MVP->model = glm::mat4(1.0f);
				MVP->model *= MVP->transform;

				renderable->GetVertexShader()->SetUniformMatrix4f("model", MVP->model, 0);

				renderable->GetVAO()->Draw(renderable->GetIBO()->getComponentCount());

				m_RenderQueue.pop_front();
			}
		}

			inline void SetViewMatrix(glm::mat4 view)
			{
				MVP->view = view;
			}
			inline void SetModelMatrix(const glm::mat4 & model)
			{
				MVP->model = model;
			}
			inline void SetProjectionMatrixPerspective(float FOV, float width, float height, float minDepth, float maxDepth)
			{
				glm::mat4 proj;
				RenderAPI api = GraphicsContext::GetAPI();
				switch (api)
				{
				case RenderAPI::API_NONE:
					DG_FATAL("Invalid render API");
					break;
				case RenderAPI::OpenGL:
					proj = glm::perspectiveFovRH_NO(glm::radians(FOV), width, height, minDepth, maxDepth);
					break;
				case RenderAPI::VULKAN:
					DG_FATAL("Not implemented");
					break;
				default:
				{
					proj = glm::perspectiveFovRH_NO(glm::radians(FOV), width, height, minDepth, maxDepth);
					DG_FATAL("Invalid render API, defaulted to OPENGL SPEC");
				}
				break;
				}
				MVP->projection = proj;
			}
			inline void SetTransformMatrix(const glm::mat4 & transform) { MVP->transform = transform; }

			inline glm::mat4 GetViewMatrix() const { return MVP->view; }
			inline glm::mat4 GetModelMatrix() const { return MVP->model; }
			inline glm::mat4 GetProjectionMatrix() const { return MVP->projection; }
			inline glm::mat4 GetTransformMatrix() const { return MVP->transform; }


			//temp
			inline void SetLight(const glm::vec3 & position, const glm::vec3 & ambient, const glm::vec3 & diffuse, glm::vec3 & specular)
			{
				m_Light.position = position;
				m_Light.ambient = ambient;
				m_Light.diffuse = diffuse;
				m_Light.specular = specular;
			}
			inline void SetViewPos(glm::vec3 pos) { m_ViewPos = pos; }

		private:
			std::deque<const OldMesh*> m_RenderQueue;
			std::unique_ptr<MatrixPass1> MVP;


			//temp
			Light1 m_Light;
			glm::vec3 m_ViewPos;


		};

	}

