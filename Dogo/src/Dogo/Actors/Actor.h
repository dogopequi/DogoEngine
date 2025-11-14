#pragma once
#include "Dogo/Renderer/AssimpModel.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
	class Actor
	{
	public:
		Actor() = delete;
		Actor(float x, float y, float z);
		~Actor();

		void Update();
		

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

	protected:
		Model* m_Model;
	};
}
