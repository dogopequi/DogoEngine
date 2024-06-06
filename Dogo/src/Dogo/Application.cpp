#include "dgpch.h"
#include "Dogo/Core.h"
#include "Application.h"
#include "Logger.h"
#include "glad/glad.h"
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
	void processInput(glm::vec3& pos, glm::vec3& front, glm::vec3& up, float time)
	{
		WindowsWindow* window = WindowsWindow::GetWindowClass(NULL);
		const float cameraSpeed = 2.5f * time; // adjust accordingly
		if (Input::IsKeyPressed(DG_KEY_W))
			pos += cameraSpeed * front;
		if (Input::IsKeyPressed(DG_KEY_S))
			pos -= cameraSpeed * front;
		if (Input::IsKeyPressed(DG_KEY_A))
			pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
		if (Input::IsKeyPressed(DG_KEY_D))
			pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;

		if (Input::IsKeyPressed(DG_KEY_L))
			window->LockCursor();
		if (Input::IsKeyPressed(DG_KEY_U))
			window->UnlockCursor();
	}
	
	Application::Application()
	{
		m_Window = Window::Create();
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
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		/*DG_TRACE(e.ToString().c_str());*/
		m_IsRunning = false;
		return true;
	}
	bool Application::KeyPressedCallBack(KeyPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
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

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
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
		fov -= Input::GetScrollDelta();
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 90.0f)
			fov = 90.0f;
		/*DG_TRACE(e.ToString().c_str());*/
		return true;
	}
#endif

	void changetexture(const std::string& filepath, ImageType imageType, TextureType textureType, Texture& texture)
	{
		if (Input::IsKeyPressed(DG_KEY_B))
		{
			texture.UpdateTexture(filepath, imageType, textureType);
		}
	}

	void Application::Run()
	{
		m_Window->SetInstance(instance);
		m_Window->Init();
		if (!m_Window->InitContext())
		{
			DG_WARN("Failed to init context");
			return;
		}

		using namespace DirectX;
		using namespace PackedVector;
		using Microsoft::WRL::ComPtr;

		float vertices[] = {
			0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f , 0.5f, 0.0f, // Red
			0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f , 1.0f, 1.0f, // Green
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 1.0f // Blue
		};
		uint32_t indices[] = {
			0, 2, 1
		};

		BufferLayout layout =
		{
			{ShaderDataType::Float3, "POSITION"},
			{ShaderDataType::Float3, "COLOR"},
			{ShaderDataType::Float2, "TEXCOORD"}
		};
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;
			layout(location = 2) in vec2 a_Texture;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			//uniform mat4 MVP;

			out vec3 v_Position;
			out vec3 v_Color;
			out vec2 v_Texture;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				v_Texture = a_Texture;
				gl_Position = projection * view * model * vec4(a_Position, 1.0);
				//gl_Position = MVP * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec3 v_Color;
			in vec2 v_Texture;

			uniform sampler2D ourTexture;
			//uniform sampler2D ourTexture1;
			void main()
			{
				//color = mix(texture(ourTexture, v_Texture), texture(ourTexture1, v_Texture), 0.2);
				color = texture(ourTexture, v_Texture);
				//color = vec4(1.0, 1.0, 1.0, 1.0);
			}
		)";

		SimpleRenderer2D Renderer;

		struct MatrixPass
		{
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;
			glm::mat4 transform;
	};
		MatrixPass stack;

#if OPENGL
		Renderer.SetVertexAndPixelShader(vertexSrc, fragmentSrc);
#endif
#if DX11
		Renderer.SetVertexAndPixelShader(L"../Dogo/resources/Shaders/vert.hlsl", L"../Dogo/resources/Shaders/pixel.hlsl");
#endif

		Renderable2D renderable1(glm::vec3(1.0f, -0.5f, 5.0f), vertices, sizeof(vertices), indices, sizeof(indices), layout, Renderer.GetVertexShader());
		Renderable2D renderable2(glm::vec3(-1.0f, -0.0f, 1.0f), vertices, sizeof(vertices), indices, sizeof(indices), layout, Renderer.GetVertexShader());

		std::shared_ptr<Texture> SmileyFace(Texture::Create("../Dogo/resources/awesomeface.png", ImageType::PNG, TextureType::twoD, "Smiley"));
		SmileyFace->Bind(0, "ourTexture");
		Renderer.SetProjectionMatrixPerspective(fov, 1280.0f, 720.0f, 0.1f, 100.0f);
		Renderer.SetViewMatrix(cameraPosition, cameraPosition + cameraFront, cameraUp);
		Renderer.SetModelMatrix(glm::mat4(1.0f));
		Renderer.SetTransformMatrix(glm::mat4(1.0f));


		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		while (m_Window->isRunning() && m_Window != nullptr)
		{
			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
			float currentFrame = timer.elapsed();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			Renderer.Submit(renderable1);
			Renderer.Submit(renderable2);
			Renderer.SetProjectionMatrixPerspective(fov,1280.0f, 720.0f, 0.1f, 100.0f);
			processInput(cameraPosition, cameraFront, cameraUp, deltaTime);
			Renderer.SetViewMatrix(cameraPosition, cameraPosition + cameraFront, cameraUp);
			changetexture("../Dogo/resources/CARDIGA.jpg", ImageType::JPG, TextureType::twoD, *SmileyFace);
			SmileyFace->Bind(0, "ourTexture");
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