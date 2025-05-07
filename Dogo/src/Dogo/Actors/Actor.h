#pragma once
#include "Dogo/Renderer/AssimpModel.h"
#include "Entity.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
	class TransformComponent;
	class StaticMeshComponent;
	class DynamicMeshComponent;
	class Actor
	{
	public:
		Actor();
		~Actor();

		void Update();
		
		inline TransformComponent* GetTC() const { return TC; }

		void SetPosition(float x, float y, float z);

		glm::vec3 GetPosition() const;

		Model* GetModel() const
		{
			return m_Model;
		}
		void AddDynamicModel(Model* model);
		void AddStaticModel(Model* model);


		void AddForce(glm::vec3 force);
		void AddImpulse(glm::vec3 force);

	private:
		DogoECS::Entity* m_Entity;
		TransformComponent* TC;
		Model* m_Model;
	};
}
