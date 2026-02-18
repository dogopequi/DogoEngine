#pragma once
#include "Dogo/Utils/Logger.h"
#include <DogoECS.h>
#include "Dogo/Audio/AudioEngine.h"
#include "glm/gtx/euler_angles.hpp"
namespace Dogo
{
	namespace ECS
	{
		inline static constexpr size_t NUM_ENTITIES = 5000;
		inline static constexpr size_t NUM_COMPONENTS = 10000;
		inline static DogoECS::DG_EntityManager entityManager(NUM_ENTITIES);
		inline static DogoECS::DG_ComponentManager componentManager(NUM_COMPONENTS, NUM_ENTITIES);

		inline DogoECS::DG_EntityManager* GetEntityManager() { return &entityManager; }
		inline DogoECS::DG_ComponentManager* GetComponentManager() { return &componentManager; }

        template<typename T>
        inline void RegisterComponent()
        {
            GetComponentManager()->RegisterComponent<T>();
        }

        template<typename T, typename... Args>
        inline T* AddComponent(DogoECS::Entity* entity, Args&&... args)
        {
            return GetComponentManager()->AddComponent<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T>
        inline T* GetComponent(uint64_t id)
        {
            return GetComponentManager()->GetComponent<T>(id);
        }
        template<typename T>
        inline T* GetComponent(DogoECS::Entity* entity)
        {
            return GetComponentManager()->GetComponent<T>(entity->GetID());
        }
        inline boolean RemoveComponents(uint64_t id)
        {
            return GetComponentManager()->RemoveComponents(id);
        }
        inline boolean RemoveComponents(DogoECS::Entity* entity)
        {
            return GetComponentManager()->RemoveComponents(entity);
        }

        template<typename T>
        inline auto GetBeginIterator()
        {
            return GetComponentManager()->AllActiveBegin<T>();
        }

        template<typename T>
        inline auto GetEndIterator()
        {
            return GetComponentManager()->AllActiveEnd<T>();
        }

        inline DogoECS::Entity* CreateEntity()
        {
            return GetEntityManager()->CreateEntity();
        }


		struct TransformComponent : public DogoECS::DG_Component
		{
            TransformComponent() : DogoECS::DG_Component(), position(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f)) {}
            TransformComponent(const glm::vec3& pos) : DogoECS::DG_Component(), position(pos), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f)) {}
            inline glm::vec3 GetPosition() const
            {
                return  position;
            }
            inline glm::vec3 GetRotationAsVec3() const
            {
                return glm::degrees(glm::eulerAngles(rotation));
            }
            inline glm::quat GetRotationAsQuat() const
            {
                return rotation;
            }
            inline glm::vec3 GetScale() const
            {
                return scale;
            }

            inline void SetPosition(const glm::vec3& pos)
            {
                position = pos;
            }
            inline void SetRotation(const glm::vec3 rot)
            {
                rotation = glm::quat(glm::radians(rot));
            }
            inline void SetRotation(const glm::quat rot)
            {
                rotation = rot;
            }
            inline void SetScale(const glm::vec3 s)
            {
                scale = s;
            }

            glm::vec3 position;
            glm::quat rotation;
            glm::vec3 scale;

		};

        struct VelocityComponent : public DogoECS::DG_Component
        {
            VelocityComponent() : DG_Component(), linearVelocity(glm::vec3(0.0f)), angularVelocity(glm::vec3(0.0f)) {}
            VelocityComponent(const glm::vec3& l, const glm::vec3& a) : DG_Component(), linearVelocity(l), angularVelocity(a) {}
            inline glm::vec3 GetAngularVelocity()
            {
                return angularVelocity;
            }
            inline glm::vec3 GetLinearVelocity()
            {
                return linearVelocity;
            }
            inline void SetLinearVelocity(const glm::vec3& v)
            {
                linearVelocity = v;
            }
            inline void SetAngularVelocity(const glm::vec3& v)
            {
                angularVelocity = v;
            }
            glm::vec3 linearVelocity;
            glm::vec3 angularVelocity;
        };


        //struct ColliderComponent : public DogoECS::DG_Component
        //{
        //    ColliderComponent() : DogoECS::DG_Component() {}
        //    ~ColliderComponent();



        //private:
        //    PxShape* shape = nullptr;
        //    PxFilterData filterData;
        //    bool trigger = false;
        //};

	}
}