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
#include "ft2build.h"
#include FT_FREETYPE_H

namespace Dogo
{
	unsigned int VAO, VBO;
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};
	std::map<GLchar, Character> Characters;
	void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
	{
		// activate corresponding render state	
		shader.Bind();
		shader.SetUniform3f("textColor", color);
		glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f);
		shader.SetUniformMatrix4f("projection", projection);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
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

		//Model* model =  new Model("../Dogo/resources/Ratchet/Ratchet.obj", layout, vertexShader, pixelShader);
		//Model* model1 = new Model("../Dogo/resources/Ship/QuarkShuttle.obj", layout, vertexShader, pixelShader);

		//Actor actor(0.0f, 5.0f, 5.0f);
		//Actor actor1(40.0f, 1.0f, 20.0f);
		//actor.AddDynamicModel(model);
		//actor1.AddStaticModel(model1);


		std::wstring vertexShader1 = L"../Dogo/resources/Shaders/linesVERT.glsl";
		std::wstring pixelShader1 = L"../Dogo/resources/Shaders/linesFRAG.glsl";
		Line line1(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), vertexShader1, pixelShader1);
		Line line2(glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), vertexShader1, pixelShader1);
		Line line3(glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), vertexShader1, pixelShader1);
		Line line4(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), vertexShader1, pixelShader1);

		Timer timer;
		
		float deltaTime{ 0.0f };
		float lastFrame{ 0.0f };
		float y = 0;
		MemoryUsage::PrintUsage();
		DG_Physics::CreatePlane(PxPlane(0, 1, 0, 5));


		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		// find path to font
		std::string font_name = "../Dogo/resources/Fonts/arial.ttf";
		if (font_name.empty())
		{
			std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
			return;
		}

		// load font as face
		FT_Face face;
		if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return;
		}
		else {
			// set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, 48);

			// disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// load first 128 characters of ASCII set
			for (unsigned char c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// generate texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<unsigned int>(face->glyph->advance.x)
				};
				Characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		// destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// configure VAO/VBO for texture quads
		// -----------------------------------
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		Shader* shader = Shader::Create(L"../Dogo/resources/Shaders/freetypevertex.glsl",
			L"../Dogo/resources/Shaders/freetypepixel.glsl");
		
		while (m_Window->isRunning() && m_Window != nullptr)
		{

			//::DG_ComponentManager::UpdateComponents<TransformComponent>();
			m_Window->ClearColor(0.2f, 1.0f, 1.0f, 1.0f);
			float currentFrame = timer.elapsed();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

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
			//Renderer.Flush();

			////////////////////////////////////////////////////////
			//UI
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			RenderText(*shader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			RenderText(*shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

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