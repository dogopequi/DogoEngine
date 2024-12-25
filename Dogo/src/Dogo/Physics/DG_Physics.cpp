#include "dgpch.h"
#include "DG_Physics.h"
namespace Dogo
{
	using namespace physx;
	physx::PxDefaultAllocator DG_Physics::gAllocator;
	physx::PxDefaultErrorCallback DG_Physics::gErrorCallback;
	physx::PxFoundation* DG_Physics::gFoundation = NULL;
	physx::PxPhysics* DG_Physics::gPhysics = NULL;
	physx::PxDefaultCpuDispatcher* DG_Physics::gDispatcher = NULL;
	physx::PxScene* DG_Physics::gScene = NULL;
	physx::PxMaterial* DG_Physics::gMaterial = NULL;
	physx::PxPvd* DG_Physics::gPvd = NULL;

	void DG_Physics::InitPhysics(const glm::vec3& gravity)
	{
		s_Instance->InitPhysicsImpl(gravity);
	}

	void DG_Physics::InitPhysicsImpl(const glm::vec3& gravity)
	{
		gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

		gPvd = PxCreatePvd(*gFoundation);
		PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

		gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

		PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
		sceneDesc.gravity = PxVec3(gravity.x, gravity.y, gravity.z);
		gDispatcher = PxDefaultCpuDispatcherCreate(2);
		sceneDesc.cpuDispatcher = gDispatcher;
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;
		gScene = gPhysics->createScene(sceneDesc);

		PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
		gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
		PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
		gScene->addActor(*groundPlane);
	}

	void DG_Physics::StepPhysics(float framerate)
	{
		s_Instance->StepPhysicsImpl(framerate);
	}

	void DG_Physics::StepPhysicsImpl(float framerate)
	{
		gScene->simulate(framerate);
		gScene->fetchResults(true);
	}
}