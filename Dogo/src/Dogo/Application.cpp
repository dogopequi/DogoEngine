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
#include "DogoECS.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>


namespace Dogo
{
	void PrintMatrix(const glm::mat4& matrix, const std::string& name)
	{
		DG_TRACE("Matrix %s:", name.c_str());
		const float* ptr = glm::value_ptr(matrix);
		for (int i = 0; i < 4; ++i)
		{
			DG_INFO("row:  %f, %f, %f, %f", ptr[i * 4 + 0], ptr[i * 4 + 1], ptr[i * 4 + 2], ptr[i * 4 + 3]);
		}
	}
	void Application::processInput(float time)
	{
		WindowsWindow* window = WindowsWindow::GetWindowClass(NULL);
		const float cameraSpeed = m_Camera->GetSpeed() * time; // adjust accordingly
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


		DogoECS::Entity* E1 = DogoECS::DG_EntityManager::CreateEntity();

		DogoECS::DG_ComponentManager::RegisterComponent<DogoECS::TransformComponent>();

		DogoECS::TransformComponent* TC = E1->AddComponent<DogoECS::TransformComponent>();

		TC->SetX(1.0f);
		TC->SetY(1.0f);
		TC->SetZ(1.0f);
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
		// if(e.GetKeyCode() == DG_KEY_ESCAPE)
		// 	ClipCursor(nullptr);
		return true;
	}
	bool Application::KeyReleasedCallBack(KeyReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Application::MouseMovedCallBack(MouseMovedEvent& e)
	{
		//TODO fix bug, the reset of the position is triggering the camera look.
		//DG_TRACE(e.ToString().c_str());
		// if (Input::GetKey() == DG_KEY_ESCAPE)
		// 	return false;
		/*RECT rect;
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
		rect.bottom = lr.y;*/


		 float xpos = static_cast<float>(Input::GetMouseX());
		 float ypos = static_cast<float>(Input::GetMouseY());

		 if (firstMouse)
		 {
		 	lastX = xpos;
		 	lastY = ypos;
		 	firstMouse = false;
		 }

		 float xoffset = xpos - lastX;
		 float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		 lastX = xpos;
		 lastY = ypos;

		 //ClipCursor(&rect);
		 //SetCursorPos(rect.left + 1280 / 2, rect.top + 720 / 2);
		 xoffset *= m_Camera->GetSensitivity();
		 yoffset *= m_Camera->GetSensitivity();

		 m_Camera->SetYaw(m_Camera->GetYaw() + xoffset);
		 m_Camera->SetPitch(m_Camera->GetPitch() + yoffset);

		 // make sure that when pitch is out of bounds, screen doesn't get flipped
		 if (true) // future a constrain pitch boolean
		 {
			 if (m_Camera->GetPitch() > 89.0f)
				 m_Camera->SetPitch(89.0f);
			 if (m_Camera->GetPitch() < -89.0f)
				 m_Camera->SetPitch(-89.0f);
		 }
		 m_Camera->UpdateVectors();
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

	void changetexture(const std::string& filepath, ImageType imageType, TextureType textureType, Texture& texture)
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

		float triangleVertices[] = {
			0.0f, 0.5f, 1.0f, 1.0f, 0.3f, 0.8f, 0.5f, 0.0f, // Red
			0.5f, -0.5f, 1.0f, 1.0f, 0.3f, 0.8f , 1.0f, 1.0f, // Green
			-0.5f, -0.5f, 1.0f, 1.0f, 0.3f, 0.8f , 0.0f, 1.0f // Blue
		};
		uint32_t triangleIndices[] = {
			0, 2, 1
		};

		BufferLayout triangleLayout =
		{
			{ShaderDataType::Float3, "POSITION"},
			{ShaderDataType::Float3, "COLOR"},
			{ShaderDataType::Float2, "TEXCOORD"}
		};
		float cubeVertices[] = {
			// Positions            // Normals          // Texture Coords
			-0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,   0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,   0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

			 0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,   0.0f, 0.0f,

			 0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,   1.0f, 0.0f
		};
		GLuint cubeIndices[] = {
			// front and back
			0, 3, 2,
			2, 1, 0,
			4, 5, 6,
			6, 7 ,4,
			// left and right
			11, 8, 9,
			9, 10, 11,
			12, 13, 14,
			14, 15, 12,
			// bottom and top
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
		BufferLayout cubeLayout =
		{
			{ShaderDataType::Float3, "POSITION"},
			{ShaderDataType::Float3, "NORMAL"},
			{ShaderDataType::Float2, "TEXCOORD"}
		};

		SimpleRenderer2D Renderer;

#if OPENGL
		std::wstring vertexShader = L"../Dogo/resources/Shaders/vert.glsl";
		std::wstring pixelShader = L"../Dogo/resources/Shaders/pixel.glsl";

		std::wstring cubeVert = L"../Dogo/resources/Shaders/cubeVERT.glsl";
		std::wstring pixelVert = L"../Dogo/resources/Shaders/cubePIXEL.glsl";

		std::wstring lightVert = L"../Dogo/resources/Shaders/lightVert.glsl";
		std::wstring lightPixel = L"../Dogo/resources/Shaders/lightPixel.glsl";
#endif
#if DX11
		std::wstring vertexShader = L"../Dogo/resources/Shaders/vert.hlsl";
		std::wstring pixelShader = L"../Dogo/resources/Shaders/pixel.hlsl";
#endif
		m_Camera.reset(new Camera());

		//Renderable2D renderable1(glm::vec3(1.0f, -0.5f, 5.0f), triangleVertices, sizeof(triangleVertices), triangleIndices, sizeof(triangleIndices), triangleLayout, vertexShader, pixelShader);
		Renderable2D renderable1(glm::vec3(1.0f, -0.5f, 5.0f), cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), cubeLayout, lightVert, lightPixel);
		//Renderable2D renderable2(glm::vec3(-1.0f, -0.0f, 1.0f), triangleVertices, sizeof(triangleVertices), triangleIndices, sizeof(triangleIndices), triangleLayout, vertexShader, pixelShader);
		Renderable2D renderable2(glm::vec3(-1.0f, -0.0f, 1.0f), cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), cubeLayout, cubeVert, pixelVert);
   	 	std::filesystem::path cwd = std::filesystem::current_path();
		DG_INFO(cwd.string().c_str()); DG_INFO("/Dogo/resources/awesomeface.png");
		//std::shared_ptr<Texture> SmileyFace(Texture::Create(cwd.string() + "/Dogo/resources/awesomeface.png", ImageType::PNG, TextureType::twoD, "Smiley"));
		//std::shared_ptr<Texture> SmileyFace(Texture::Create("../Dogo/resources/awesomeface.png", ImageType::PNG, TextureType::twoD, "Smiley"));
		std::shared_ptr<Texture> brick(Texture::Create("../Dogo/resources/container2.png", ImageType::PNG, TextureType::twoD, "container2.png"));
		std::shared_ptr<Texture> brickSpec(Texture::Create("../Dogo/resources/container2_specular.png", ImageType::PNG, TextureType::twoD, "container2_specular.png"));
		std::shared_ptr<Texture> light(Texture::Create("../Dogo/resources/matrix.jpg", ImageType::JPG, TextureType::twoD, "matrix.jpg"));
		Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(), 1280.0f, 720.0f, 0.1f, 100.0f);
		Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
		Renderer.SetModelMatrix(glm::mat4(1.0f));
		Renderer.SetTransformMatrix(glm::mat4(1.0f));

		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		glm::vec3 objcolor(1.0f, 0.3f, 0.8f);

		renderable2.SetColor(objcolor);

		renderable2.SetMaterial(
			brick,
			brickSpec,
			light,
			100.0f
		);
		Renderer.SetLight(
			renderable1.GetPosition(),
			glm::vec3(0.2f, 0.2f, 0.2f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);


		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		MemoryUsage::PrintUsage();
		while (m_Window->isRunning() && m_Window != nullptr)
		{
			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
			float currentFrame = timer.elapsed();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			Renderer.Submit(renderable1);
			Renderer.Submit(renderable2);
			Renderer.SetViewPos(m_Camera->GetPosition());
			Renderer.SetProjectionMatrixPerspective(m_Camera->GetZoom(),1280.0f, 720.0f, 0.1f, 100.0f);
			processInput(deltaTime);
			Renderer.SetViewMatrix(m_Camera->GetViewMatrix());
			// changetexture("../Dogo/resources/CARDIGA.jpg", ImageType::JPG, TextureType::twoD, *SmileyFace);
			Renderer.Flush();

			DogoECS::DG_ComponentManager::Update();
			//DG_TRACE("running");
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