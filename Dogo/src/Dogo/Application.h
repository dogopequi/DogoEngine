#pragma once
#include "Dogo/Core.h"
#include "Graphics/Window.h"
#include "LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Graphics/WindowsWindow.h"
#include "Renderer/Camera.h"
#include "PxPhysicsAPI.h"
#include "SnippetPrint.h"
#include "SnippetPVD.h"
#include "SnippetUtils.h"
#include "foundation/PxPhysicsVersion.h"

namespace Dogo
{
	#if DG_PLATFORM_WINDOWS
	 
	#endif
	class DG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();
		void OnEvent(Event& e);
#if DG_PLATFORM_WINDOWS
		void SetWindowsInstance(HINSTANCE instance);
#endif
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool KeyPressedCallBack(KeyPressedEvent& e);
		bool KeyReleasedCallBack(KeyReleasedEvent& e);
		bool MouseMovedCallBack(MouseMovedEvent& e);
		bool MouseButtonPressedCallBack(MouseButtonPressedEvent& e);
		bool MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e);
		bool MouseScrolledCallBack(MouseScrolledEvent& e);
	private:
		DG_Window* m_Window;
		LayerStack m_LayerStack;

		bool m_IsRunning;


		//temp
		bool firstMouse = true;
		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;

		//temp
		void processInput(float time);
		
		std::shared_ptr<Camera> m_Camera;
#if DG_PLATFORM_WINDOWS
		HINSTANCE instance;
#endif




		//////////PHYX STUFF FOR TEST

		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultErrorCallback gErrorCallback;
		physx::PxFoundation* gFoundation = NULL;
		physx::PxPhysics* gPhysics = NULL;
		physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
		physx::PxScene* gScene = NULL;
		physx::PxMaterial* gMaterial = NULL;
		physx::PxPvd* gPvd = NULL;
		physx::PxReal stackZ = 10.0f;

		physx::PxRigidDynamic* createDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity);

		void createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent);

		void initPhysics(bool interactive);

		void stepPhysics(bool /*interactive*/);

		void cleanupPhysics(bool /*interactive*/);

		void keyPress(unsigned char key, const physx::PxTransform& camera);
		int snippetMain();
	};
	Application* CreateApplication();
}



