#include "dgpch.h"
#include "Dogo/Core.h"
#include "Application.h"
#include "Logger.h"
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
#include "Physics/DG_Physics.h"
#include "DogoECS.h"
#include "Component/Component.h"
#include "Actors/Actor.h"
#include "Dogo/Renderer/Line.h"
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
		DogoECS::Init();
		DG_Physics::InitPhysics(glm::vec3(0.0f, -9.81f, 0.0f));
		DogoECS::DG_ComponentManager::RegisterComponent<TransformComponent>();

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

		Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(), 1280.0f, 720.0f, 0.1f, 1000.0f);
		Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
		Renderer.SetModelMatrix(glm::mat4(1.0f));
		Renderer.SetTransformMatrix(glm::mat4(1.0f));

		Model* model =  new Model("../Dogo/resources/Ratchet/Ratchet.obj", glm::vec3(0.0f, 0.0f, 0.0f), layout, vertexShader, pixelShader);
		Model* model1 = new Model("../Dogo/resources/Ship/QuarkShuttle.obj", glm::vec3(0.0f, 0.0f, 0.01f), layout, vertexShader, pixelShader);

		Actor actor(model);
		Actor actor1(model1);
		DogoECS::DG_ComponentManager::UpdateComponents<TransformComponent>();


		std::wstring vertexShader1 = L"../Dogo/resources/Shaders/linesVERT.glsl";
		std::wstring pixelShader1 = L"../Dogo/resources/Shaders/linesFRAG.glsl";
		Line line1(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), vertexShader1, pixelShader1);
		Line line2(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), vertexShader1, pixelShader1);
		Line line3(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), vertexShader1, pixelShader1);

		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		MemoryUsage::PrintUsage();

		while (m_Window->isRunning() && m_Window != nullptr)
		{
			DogoECS::DG_ComponentManager::UpdateComponents<TransformComponent>();
			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
			float currentFrame = timer.elapsed();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			DG_Physics::StepPhysics(deltaTime);
			Renderer.Submit(*model);
			Renderer.Submit(*model1);
			Renderer.Submit(line1);
			Renderer.Submit(line2);
			Renderer.Submit(line3);
			Renderer.SetViewPos(m_Camera->GetPosition());
			Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(),1280.0f, 720.0f, 0.1f, 100.0f);
			processInput(deltaTime);
			Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
			Renderer.Flush();

#if OPENGL
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				switch (err) {
				case GL_INVALID_ENUM:
					std::cout << "OpenGL Error: GL_INVALID_ENUM" << std::endl;
					break;
				case GL_INVALID_VALUE:
					std::cout << "OpenGL Error: GL_INVALID_VALUE" << std::endl;
					break;
				case GL_INVALID_OPERATION:
					std::cout << "OpenGL Error: GL_INVALID_OPERATION" << std::endl;
					break;
				case GL_STACK_OVERFLOW:
					std::cout << "OpenGL Error: GL_STACK_OVERFLOW" << std::endl;
					break;
				case GL_STACK_UNDERFLOW:
					std::cout << "OpenGL Error: GL_STACK_UNDERFLOW" << std::endl;
					break;
				case GL_OUT_OF_MEMORY:
					std::cout << "OpenGL Error: GL_OUT_OF_MEMORY" << std::endl;
					break;
					// Add more cases as needed
				default:
					std::cout << "Unknown OpenGL Error" << std::endl;
					break;
				}
			}
#endif
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		// 	// MemoryUsage::PrintUsage();
		}
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
}