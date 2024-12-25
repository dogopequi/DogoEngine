#pragma once
#include <glm/glm.hpp>
#include "PxPhysicsAPI.h"
#include "SnippetPrint.h"
#include "SnippetPVD.h"
#include "SnippetUtils.h"
#include "foundation/PxPhysicsVersion.h"
namespace Dogo
{
	using namespace physx;
	class DG_Physics
	{
	public:
		DG_Physics(const DG_Physics&) = delete;
		DG_Physics& operator=(const DG_Physics&) = delete;

		static void InitPhysics(const glm::vec3& gravity);

		static void StepPhysics(float framerate);

		static PxShape* GetShape(float x, float y, float z)
		{
			return gPhysics->createShape(physx::PxBoxGeometry(x, y, z), *gMaterial);
		}
		static PxRigidDynamic* GetRigidDynamic(const  physx::PxTransform& t, const  physx::PxTransform& q)
		{
			return gPhysics->createRigidDynamic(t.transform(q));
		}
		static PxRigidStatic* GetRigidStatic(const  physx::PxTransform& t, const  physx::PxTransform& q)
		{
			return gPhysics->createRigidStatic(t.transform(q));
		}
		static void AddActor(physx::PxActor* actor)
		{
			gScene->addActor(*actor);
		}
	private:
		inline void Cleanup()
		{
			PX_RELEASE(gScene);
			PX_RELEASE(gDispatcher);
			PX_RELEASE(gPhysics);
			if (gPvd)
			{
				physx::PxPvdTransport* transport = gPvd->getTransport();
				PX_RELEASE(gPvd);
				PX_RELEASE(transport);
			}
			PX_RELEASE(gFoundation);
		}
		static void StepPhysicsImpl(float framerate);
		static void InitPhysicsImpl(const glm::vec3& gravity);
	protected:
		DG_Physics() = default;
	private:
		static DG_Physics* s_Instance;
		static physx::PxDefaultAllocator gAllocator;
		static physx::PxDefaultErrorCallback gErrorCallback;
		static physx::PxFoundation* gFoundation;
		static physx::PxPhysics* gPhysics;
		static physx::PxDefaultCpuDispatcher* gDispatcher;
		static physx::PxScene* gScene;
		static physx::PxMaterial* gMaterial;
		static physx::PxPvd* gPvd;
	};
}
