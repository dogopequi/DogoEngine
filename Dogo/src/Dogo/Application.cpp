#include "dgpch.h"
#include "Dogo/Core.h"
#include "Application.h"
#include "Logger.h"
//#include "glad/glad.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Dogo/Timer.h"
#include "Dogo/Input/WindowsInput.h"
#include "Platform/DX11/DX11Context.h"
#include "Platform//DX11/DX11Texture.h"
#include "Platform/DX11/DX11IndexBuffer.h"
#include "Platform/DX11/DX11VertexBuffer.h"
#include <stb/stb_image.h>
#include "Platform/DX11/DX11Shader.h"
#include "Dogo/Renderer/Renderable2D.h"
#include "Dogo/Renderer/SimpleRenderer2D.h"
#include "Dogo/DogoMemory.h"
#include "Renderer/Mesh.h"
#include "Renderer/MeshRenderer.h"
#include "Renderer/AssimpModel.h"
#include "Renderer/AssimpRenderer.h"
#include "DogoECS.h"

class TransformComponent : public DogoECS::DG_Component
{
public:
	TransformComponent(uint64_t id) : DogoECS::DG_Component(id) { /*std::cout << "Transform Component created" << std::endl;*/ }
	TransformComponent() : DogoECS::DG_Component() {}
	~TransformComponent() override {/* std::cout << "Transform Component deleted" << std::endl;*/ }


	void Update() override
	{
		std::cout << "TRANSFORM --------------------------------------------------" << std::endl;
		std::cout << "X: " << x << std::endl;
		std::cout << "Y: " << y << std::endl;
		std::cout << "Z: " << z << std::endl;
		std::cout << "ID: " << m_ComponentID.GetUUID_ui64() << std::endl;
	}

	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }

private:
	float x, y, z;

};
namespace DogoECS
{
	template<>
	REGISTER_COMPONENT_TEMPLATE(TransformComponent)

		template<>
	ADD_COMPONENT_TEMPLATE(TransformComponent)

		template <>
	REMOVE_COMPONENT_TEMPLATE(TransformComponent)

		template<>
	UPDATE_COMPONENTS_TEMPLATE(TransformComponent)

}
 class AudioComponent : public DogoECS::DG_Component
    {
    public:
        AudioComponent(uint64_t id) : DogoECS::DG_Component(id) {}
        AudioComponent() : DogoECS::DG_Component() {}

        ~AudioComponent() override { }


        void Update() override
        {

            std::cout << "AUDIO --------------------------------------------------- " << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "ID: " << m_ComponentID.GetUUID_ui64() << std::endl;
        }

        void SetName(std::string name) { this->name = name; }
        std::string GetName() const { return name; }

    private:
        std::string name;
    };

	namespace DogoECS
	{
    template<>
    REGISTER_COMPONENT_TEMPLATE(AudioComponent)

        template<>
    ADD_COMPONENT_TEMPLATE(AudioComponent)

        template <>
    REMOVE_COMPONENT_TEMPLATE(AudioComponent)

        template<>
    UPDATE_COMPONENTS_TEMPLATE(AudioComponent)

}

namespace Dogo
{
	void Application::processInput(float time)
	{
		WindowsWindow* window = WindowsWindow::GetWindowClass(NULL);
		const float cameraSpeed = m_Camera->GetSpeed() * time;
		if (Input::IsKeyPressed(DG_KEY_W))
			m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetSpeed() * m_Camera->GetFront());
		if (Input::IsKeyPressed(DG_KEY_S))
			m_Camera->SetPosition(m_Camera->GetPosition() - m_Camera->GetSpeed() * m_Camera->GetFront());
		if (Input::IsKeyPressed(DG_KEY_A))
			m_Camera->SetPosition(m_Camera->GetPosition() - m_Camera->GetSpeed() * m_Camera->GetRight());
		if (Input::IsKeyPressed(DG_KEY_D))
			m_Camera->SetPosition(m_Camera->GetPosition() + m_Camera->GetSpeed() * m_Camera->GetRight());

		if (Input::IsKeyPressed(DG_KEY_L))
			window->LockCursor();
		if (Input::IsKeyPressed(DG_KEY_U))
			window->UnlockCursor();
	}
	
	Application::Application()
	{
		m_Window = DG_Window::Create();
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Application::OnEvent));
		m_IsRunning = true;
	}
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
#if DG_PLATFORM_WINDOWS
	void Application::SetWindowsInstance(HINSTANCE instance)
	{
		this->instance = instance;
	}
#endif
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		m_IsRunning = false;
		return true;
	}
	bool Application::KeyPressedCallBack(KeyPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		 if(e.GetKeyCode() == DG_KEY_ESCAPE)
		 	ClipCursor(nullptr);
		return true;
	}
	bool Application::KeyReleasedCallBack(KeyReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Application::MouseMovedCallBack(MouseMovedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());

		if (Input::GetKey() == DG_KEY_ESCAPE)
			return false;

		RECT rect;
		WindowsWindow* window = (WindowsWindow*)m_Window;
		GetClientRect(window->GetHandle(), &rect);

		POINT ul;
		ul.x = rect.left;
		ul.y = rect.top;

		POINT lr;
		lr.x = rect.right;
		lr.y = rect.bottom;

		MapWindowPoints(window->GetHandle(), nullptr, &ul, 1);
		MapWindowPoints(window->GetHandle(), nullptr, &lr, 1);

		rect.left = ul.x;
		rect.top = ul.y;
		rect.right = lr.x;
		rect.bottom = lr.y;

		float xpos = static_cast<float>(Input::GetMouseX());
		float ypos = static_cast<float>(Input::GetMouseY());

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = 1280 / 2;
		lastY = 720 / 2;

		xoffset *= m_Camera->GetSensitivity();
		yoffset *= m_Camera->GetSensitivity();

	
		m_Camera->SetYaw(m_Camera->GetYaw() + xoffset);
		m_Camera->SetPitch(m_Camera->GetPitch() + yoffset);

		if (m_Camera->GetPitch() > 89.0f)
			m_Camera->SetPitch(89.0f);
		if (m_Camera->GetPitch() < -89.0f)
			m_Camera->SetPitch(-89.0f);

		m_Camera->UpdateVectors();

		ClipCursor(&rect);

		SetCursorPos(rect.left + 1280 / 2, rect.top + 720 / 2);

		return true;
	}
	bool Application::MouseButtonPressedCallBack(MouseButtonPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Application::MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Application::MouseScrolledCallBack(MouseScrolledEvent& e)
	{
		m_Camera->SetZoom(m_Camera->GetZoom() - Input::GetScrollDelta());
		if ((m_Camera->GetZoom() < 1.0f))
			m_Camera->SetZoom(1.0f);
		if ((m_Camera->GetZoom() > 90.0f))
			m_Camera->SetZoom(90.0f);
		//DG_TRACE(e.ToString().c_str());
		return true;
	}

	void changetexture(const std::string& filepath, const std::string& imageType, TextureType textureType, Texture& texture)
	{
		if (Input::IsKeyPressed(DG_KEY_B))
		{
			texture.UpdateTexture(filepath, imageType, textureType);
		}
	}

	void Application::Run()
	{
		MemoryUsage::PrintUsage();
		#if DG_PLATFORM_WINDOWS
		m_Window->SetInstance(instance);
		m_Window->Init();
		#endif

		BufferLayout layout =
		{
			{ShaderDataType::Float3, "POSITION"},
			{ShaderDataType::Float3, "NORMAL"},
			{ShaderDataType::Float2, "TEXCOORD"}
		};

		AssimpRenderer Renderer;

		std::wstring vertexShader = L"../Dogo/resources/Shaders/meshVERT.glsl";
		std::wstring pixelShader = L"../Dogo/resources/Shaders/meshPIXEL.glsl";

		m_Camera.reset(new Camera());

		Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(), 1280.0f, 720.0f, 0.1f, 100.0f);
		Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
		Renderer.SetModelMatrix(glm::mat4(1.0f));
		Renderer.SetTransformMatrix(glm::mat4(1.0f));

		Model model("../Dogo/resources/Ratchet/Ratchet.obj", glm::vec3(0.0f, 0.0f, 0.0f), layout, vertexShader, pixelShader);
		Model model1("../Dogo/resources/Ship/QuarkShuttle.obj", glm::vec3(0.0f, 0.0f, 100.0f), layout, vertexShader, pixelShader);


		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		MemoryUsage::PrintUsage();
		DogoECS::Init();
		DogoECS::DG_ComponentManager::RegisterComponent<TransformComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<AudioComponent>();
		DogoECS::Entity* e1 = DogoECS::DG_EntityManager::CreateEntity();
		TransformComponent* tc1 = e1->AddComponent<TransformComponent>();
		AudioComponent* ac1 = e1->AddComponent<AudioComponent>();
		snippetMain();
//		while (m_Window->isRunning() && m_Window != nullptr)
//		{
//			DogoECS::DG_ComponentManager::UpdateComponents<AudioComponent>();
//			DogoECS::DG_ComponentManager::UpdateComponents<TransformComponent>();
//			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
//			float currentFrame = timer.elapsed();
//			deltaTime = currentFrame - lastFrame;
//			lastFrame = currentFrame;
//
//			Renderer.Submit(model);
//			Renderer.Submit(model1);
//			Renderer.SetViewPos(m_Camera->GetPosition());
//			Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(),1280.0f, 720.0f, 0.1f, 100.0f);
//			processInput(deltaTime);
//			Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
//			Renderer.Flush();
//
//#if OPENGL
//			GLenum err;
//			while ((err = glGetError()) != GL_NO_ERROR) {
//				switch (err) {
//				case GL_INVALID_ENUM:
//					std::cout << "OpenGL Error: GL_INVALID_ENUM" << std::endl;
//					break;
//				case GL_INVALID_VALUE:
//					std::cout << "OpenGL Error: GL_INVALID_VALUE" << std::endl;
//					break;
//				case GL_INVALID_OPERATION:
//					std::cout << "OpenGL Error: GL_INVALID_OPERATION" << std::endl;
//					break;
//				case GL_STACK_OVERFLOW:
//					std::cout << "OpenGL Error: GL_STACK_OVERFLOW" << std::endl;
//					break;
//				case GL_STACK_UNDERFLOW:
//					std::cout << "OpenGL Error: GL_STACK_UNDERFLOW" << std::endl;
//					break;
//				case GL_OUT_OF_MEMORY:
//					std::cout << "OpenGL Error: GL_OUT_OF_MEMORY" << std::endl;
//					break;
//					// Add more cases as needed
//				default:
//					std::cout << "Unknown OpenGL Error" << std::endl;
//					break;
//				}
//			}
//#endif
//			for (Layer* layer : m_LayerStack)
//				layer->OnUpdate();
//			m_Window->OnUpdate();
//		// 	// MemoryUsage::PrintUsage();
//		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(DG_BIND_EVENT_FN(Application::KeyPressedCallBack));
		dispatcher.Dispatch<KeyReleasedEvent>(DG_BIND_EVENT_FN(Application::KeyReleasedCallBack));
		dispatcher.Dispatch<MouseMovedEvent>(DG_BIND_EVENT_FN(Application::MouseMovedCallBack));
		dispatcher.Dispatch<MouseButtonPressedEvent>(DG_BIND_EVENT_FN(Application::MouseButtonPressedCallBack));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(Application::MouseButtonReleasedCallBack));
		dispatcher.Dispatch<MouseScrolledEvent>(DG_BIND_EVENT_FN(Application::MouseScrolledCallBack));
	}



	///////////////// PHYSX STUFF FOR TESTS

	physx::PxRigidDynamic* Application::createDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity = physx::PxVec3(0))
	{
		physx::PxRigidDynamic* dynamic = physx::PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
		dynamic->setAngularDamping(0.5f);
		dynamic->setLinearVelocity(velocity);
		gScene->addActor(*dynamic);
		return dynamic;
	}

	void Application::createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent)
	{
		physx::PxShape* shape = gPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);
		for (physx::PxU32 i = 0; i < size; i++)
		{
			for (physx::PxU32 j = 0; j < size - i; j++)
			{
				physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
				physx::PxRigidDynamic* body = gPhysics->createRigidDynamic(t.transform(localTm));
				body->attachShape(*shape);
				physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
				gScene->addActor(*body);
			}
		}
		shape->release();
	}

	void Application::initPhysics(bool interactive)
	{
		gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

		gPvd = physx::PxCreatePvd(*gFoundation);
		physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		gPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

		gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, gPvd);

		physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
		sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
		gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		sceneDesc.cpuDispatcher = gDispatcher;
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		gScene = gPhysics->createScene(sceneDesc);

		physx::PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
		gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

		physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*gPhysics, physx::PxPlane(0, 1, 0, 0), *gMaterial);
		gScene->addActor(*groundPlane);

		for (physx::PxU32 i = 0; i < 5; i++)
			createStack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);

		if (!interactive)
			createDynamic(physx::PxTransform(physx::PxVec3(0, 40, 100)), physx::PxSphereGeometry(10), physx::PxVec3(0, -50, -100));
	}

	void Application::stepPhysics(bool /*interactive*/)
	{
		gScene->simulate(1.0f / 60.0f);
		gScene->fetchResults(true);
	}

	void Application::cleanupPhysics(bool /*interactive*/)
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

		printf("SnippetHelloWorld done.\n");
	}

	void Application::keyPress(unsigned char key, const physx::PxTransform& camera)
	{
		switch (toupper(key))
		{
		case 'B':	createStack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);						break;
		case ' ':	createDynamic(camera, physx::PxSphereGeometry(3.0f), camera.rotate(physx::PxVec3(0, 0, -1)) * 200);	break;
		}
	}
	int Application::snippetMain()
	{
#ifdef RENDER_SNIPPET
		extern void renderLoop();
		renderLoop();
#else
		const physx::PxU32 frameCount = 1000000;
		initPhysics(false);
		for (physx::PxU32 i = 0; i < frameCount; i++)
			stepPhysics(false);
		cleanupPhysics(false);
#endif

		return 0;
	}

}