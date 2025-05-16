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
#include <stb/stb_image.h>
#include "Dogo/Renderer/Renderable2D.h"
#include "Dogo/Renderer/SimpleRenderer2D.h"
#include "Dogo/DogoMemory.h"
#include "Renderer/AssimpModel.h"
#include "Renderer/AssimpRenderer.h"
#include "Physics/DG_Physics.h"
#include "DogoECS.h"
#include "Component/Component.h"
#include "Actors/Actor.h"
#include "Dogo/Renderer/Line.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"

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
		/*DG_TRACE(e.ToString().c_str());*/
		m_IsRunning = false;
		return true;
	}
	bool Application::KeyPressedCallBack(KeyPressedEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/
		 if(e.GetKeyCode() == DG_KEY_ESCAPE)
		 	ClipCursor(nullptr);
		return true;
	}
	bool Application::KeyReleasedCallBack(KeyReleasedEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/
		return true;
	}
	bool Application::MouseMovedCallBack(MouseMovedEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/

		//if (Input::GetKey() == DG_KEY_ESCAPE)
		//	return false;

		//RECT rect;
		//WindowsWindow* window = (WindowsWindow*)m_Window;
		//GetClientRect(window->GetHandle(), &rect);

		//POINT ul;
		//ul.x = rect.left;
		//ul.y = rect.top;

		//POINT lr;
		//lr.x = rect.right;
		//lr.y = rect.bottom;

		//MapWindowPoints(window->GetHandle(), nullptr, &ul, 1);
		//MapWindowPoints(window->GetHandle(), nullptr, &lr, 1);

		//rect.left = ul.x;
		//rect.top = ul.y;
		//rect.right = lr.x;
		//rect.bottom = lr.y;

		//float xpos = static_cast<float>(Input::GetMouseX());
		//float ypos = static_cast<float>(Input::GetMouseY());

		//if (firstMouse)
		//{
		//	lastX = xpos;
		//	lastY = ypos;
		//	firstMouse = false;
		//}

		//float xoffset = xpos - lastX;
		//float yoffset = lastY - ypos;

		//lastX = 1280 / 2;
		//lastY = 720 / 2;

		//xoffset *= m_Camera->GetSensitivity();
		//yoffset *= m_Camera->GetSensitivity();

	
		//m_Camera->SetYaw(m_Camera->GetYaw() + xoffset);
		//m_Camera->SetPitch(m_Camera->GetPitch() + yoffset);

		//if (m_Camera->GetPitch() > 89.0f)
		//	m_Camera->SetPitch(89.0f);
		//if (m_Camera->GetPitch() < -89.0f)
		//	m_Camera->SetPitch(-89.0f);

		//m_Camera->UpdateVectors();

		//ClipCursor(&rect);

		//SetCursorPos(rect.left + 1280 / 2, rect.top + 720 / 2);

		return true;
	}
	bool Application::MouseButtonPressedCallBack(MouseButtonPressedEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/
		return true;
	}
	bool Application::MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/
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
		DogoECS::DG_ComponentManager::RegisterComponent<BaseComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<DynamicMeshComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<TransformComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<StaticMeshComponent>();

		#if DG_PLATFORM_WINDOWS
		m_Window->SetInstance(instance);
		m_Window->Init();
		#endif
		m_Camera.reset(new Camera());

		/*BufferLayout layout =
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

		Model* model =  new Model("../Dogo/resources/Ratchet/Ratchet.obj", layout, vertexShader, pixelShader);
		Model* model1 = new Model("../Dogo/resources/Ship/QuarkShuttle.obj", layout, vertexShader, pixelShader);

		Actor actor(0.0f, 5.0f, 5.0f);
		Actor actor1(40.0f, 1.0f, 20.0f);
		actor.AddDynamicModel(model);
		actor1.AddStaticModel(model1);


		std::wstring vertexShader1 = L"../Dogo/resources/Shaders/linesVERT.glsl";
		std::wstring pixelShader1 = L"../Dogo/resources/Shaders/linesFRAG.glsl";
		Line line1(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), vertexShader1, pixelShader1);
		Line line2(glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), vertexShader1, pixelShader1);
		Line line3(glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), vertexShader1, pixelShader1);
		Line line4(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), vertexShader1, pixelShader1);*/

		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		MemoryUsage::PrintUsage();
		//DG_Physics::CreatePlane(PxPlane(0, 1, 0, 5));
		Renderer2D* Renderer = Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl");
		Renderer->SetViewMatrix(glm::mat4(1.0f));
		Renderer->SetProjectionMatrix(glm::orthoRH_NO(
			0.0f,
			static_cast<float>(m_Window->GetWidth()),
			static_cast<float>(m_Window->GetHeight()),
			0.0f,
			-1.0f,
			1.0f));

		glm::mat4 model = glm::mat4(1.0f);
		Renderer->SetModelMatrix(model);
		Renderer->SetTransformMatrix(glm::mat4(1.0f));
		Texture* lebron = Texture::Create("../Dogo/resources/Textures/lebron.png", "legacy", TextureType::twoD, "lebron");
		Texture* rat = Texture::Create("../Dogo/resources/Textures/rat.png", "legacy", TextureType::twoD, "rat");
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		Renderer->LoadFont("../Dogo/resources/Fonts/arial.ttf", 48);
		static constexpr int NUM_ROWS = 100;
		static constexpr int NUM_COLS = 100;
		static constexpr float QUAD_SIZE = 5.0f;
		static constexpr float PADDING = 2.0f;
		std::shared_ptr<DogoUI::UIButton> button = std::make_shared<DogoUI::UIButton>();
		std::shared_ptr<DogoUI::UIPanel> panel = std::make_shared<DogoUI::UIPanel>();
		DogoUI::AddElement(button);
		DogoUI::AddElement(panel);
		button->visible = true;
		panel->visible = false;
		button->text = "Click Me!";
		button->pos = { 100.0f, 100.0f };
		button->size = { 200.0f, 60.0f };
		button->onClick = []() { DG_INFO("Button Clicked!"); };
		panel->color = { 0.0f, 1.0f, 0.0f };
		panel->pos = { 0.0f, 0.0f };
		panel->size = { 1280.0f, 720.0f };
		while (m_Window->isRunning() && m_Window != nullptr)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			DogoECS::DG_ComponentManager::UpdateComponents<TransformComponent>();
			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
			float currentFrame = timer.elapsed();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			float fps = 1.0f / deltaTime;
			//Renderer->Flush();
			//////////////////////////////////////////////////////
			//2D
			//if (Input::IsKeyPressed(DG_KEY_A))
			//{
			//	pos.x -= 0.5f;
			//}
			//if (Input::IsKeyPressed(DG_KEY_D))
			//{
			//	pos.x += 0.5f;
			//}
			//if (Input::IsKeyPressed(DG_KEY_W))
			//{
			//	pos.y -= 0.5f;
			//}
			//if (Input::IsKeyPressed(DG_KEY_S))
			//{
			//	pos.y += 0.5f;
			//}
			////DG_INFO("X: %f Y: %f", pos.x, pos.y);
			// QUAD WORKING 
			//Renderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 20.0f, 0.0f)), false);
			//Renderer->Submit(CreateQuad(0.0f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f }, 50.0f, 0.0f));
			//Renderer->Pop();
			//
			//// --- TRIANGLE --- WORKING
			//Renderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(220.0f, 70.0f, 0.0f)), false);
			//Renderer->Submit(CreateTriangle(0.0f, { 1.0f, 0.0f, 1.0f, 1.0f }, 50.0f, 0.0f));
			//Renderer->Pop();
			//
		 //////--- CIRCLE --- WORKING
			//Renderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 200.0f, 0.0f)), false);
			//Renderer->Submit(GenerateCircle({ 0.0f, 0.0f }, 25.0f, { 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f));
			//Renderer->Pop();
			////
			////// --- ROUNDED RECT --- WORKING
			//Renderer->Push(glm::scale(glm::translate(glm::mat4(1.0f), pos), glm::vec3(5.0f, 5.0f, 5.0f)), false);
			//Renderer->Submit(CreateRoundedRect(
			//	{ 0.0f, 0.0f },          
			//	{ 200.0f, 60.0f },        
			//	90.0f,                    
			//	{ 1.0f, 0.0f, 0.0f, 1.0f }, 
			//	0.0f
			//));
			//Renderer->Pop();

			////// --- THICK LINE --- WORKING
			//Renderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), false);
			//Renderer->Submit(CreateThickLine({ 0.0f, 0.0f }, { 1200.0f, 700.0f }, 5.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f));
			//Renderer->Pop();
			////
			////// --- LINE2D --- WORKING
			//Renderer->Push(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), false);
			//float y = m_Window->GetHeight() / 2.0f; // center of screen
			//Renderer->Submit(CreateLine2D(
			//	{ 0.0f, y, 0.0f },
			//	{ static_cast<float>(m_Window->GetWidth()), y, 0.0f },
			//	{ 0.0f, 0.0f, 1.0f, 1.0f } // red line
			//));
			//Renderer->Pop();
			//Renderer->Flush();
			Renderer->RenderText("FPS: ", 25.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));
			Renderer->RenderText(std::to_string(fps).c_str(), 135.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));

			//////////////////////////////////////////////////////
			//UI

			std::pair<uint32_t, uint32_t> mouse = Input::GetMousePosition();
			DogoUI::HandleInput(glm::vec2(mouse.first, mouse.second), Input::IsMouseButtonPressed(DG_MOUSE_BUTTON_1));
			DogoUI::Render(Renderer);

			Renderer->RenderText("FPS: ", 25.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));
			Renderer->RenderText(std::to_string(fps).c_str(), 135.0f, 570.0f, 1.0f, glm::vec3(0.0f, .0f, 1.0f));
			Renderer->Flush();
			///////////////////////////////////////////////////////
			//3D

			//glm::vec3 force(0.0f, 0.0f, 0.05f);
			//if (Input::IsKeyPressed(DG_KEY_V))
			//{
			//	actor.AddImpulse(force);
			//}
			//DG_Physics::StepPhysics(deltaTime);
			//Renderer.Submit(actor);
			//Renderer.Submit(actor1);
			//Renderer.Submit(line1);
			//Renderer.Submit(line2);
			//Renderer.Submit(line3);
			//Renderer.Submit(line4);
			//Renderer.SetViewPos(m_Camera->GetPosition());
			//Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(),1280.0f, 720.0f, 0.1f, 100.0f);
			//processInput(deltaTime);
			//Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
			//Renderer->Flush();


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
		 	 MemoryUsage::PrintUsage();
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