#pragma once
#include <DogoECS.h>
#include "Dogo/Renderer/2D/Sprite.h"
#include "Dogo/Physics/DG_Physics.h"
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
        inline T* GetComponent(DogoECS::Entity* entity)
        {
            return GetComponentManager()->GetComponent<T>(entity->GetID());
        }

        template<typename T>
        inline T* GetComponent(uint32_t id)
        {
            return GetComponentManager()->GetComponent<T>(id);
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


		struct SpriteRendererComponent : public DogoECS::DG_Component
		{
			SpriteRendererComponent();
			Sprite sprite{};

			void Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY);
			//layer
			//layer id
		};

        struct ColliderComponent : public DogoECS::DG_Component
        {
            ColliderComponent() : DogoECS::DG_Component() {}
            ~ColliderComponent();



        private:
            PxShape* shape = nullptr;
            PxFilterData filterData;
            bool trigger = false;
        };

        struct RigidBodyComponent : public DogoECS::DG_Component
        {
            RigidBodyComponent() : DogoECS::DG_Component() {}
            ~RigidBodyComponent();
            void Init(const glm::vec3& pos, const glm::vec3& shape, bool kinematic);
            void ApplyKinematic();
            inline void ApplyGravity() {
                rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
            }
            inline void DisableGravity() {
                rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
            }
            friend class PhysicsSystem;
            friend class MovementSystem;
            friend class SpriteRenderSystem2D;
            friend class AudioSystem;

        private:
            PxRigidDynamic* rigidBody = nullptr;
            float mass = 1.0f;
            bool kinematic = false;
            PxShape* shape = nullptr;
            PxFilterData filterData;
            bool hasGravity = true;
        };

        struct AudioSourceComponent : public DogoECS::DG_Component
        {
            ALuint source = 0;
            ALuint buffer = 0;
            AudioData audioData;
            std::string wavpath;
            float volume = 0.0f;
            std::string GetFilePath() const { return wavpath; }
            void SetFilePath(const std::string& filepath) { wavpath = filepath; }
            float GetVolume() const { return volume; }
            void SetVolume(float vol) { volume = vol; }
            void Play();
            ~AudioSourceComponent();
        protected:
            bool LoadCommon();
            AudioSourceComponent(const std::string& filepath, float vol);
            AudioSourceComponent();
        };

        struct AudioSourceComponent2D : public AudioSourceComponent
        {
            bool Load();
            AudioSourceComponent2D(const std::string& filepath, float vol);
            AudioSourceComponent2D() {}
            ~AudioSourceComponent2D() {}
        };
        struct AudioSourceComponent3D : public AudioSourceComponent
        {
            bool Load();
            AudioSourceComponent3D(const std::string& filepath, float vol);
            AudioSourceComponent3D() {}
            ~AudioSourceComponent3D() {}
        };

	}
}