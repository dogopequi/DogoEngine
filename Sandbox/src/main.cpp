#include "dgpch.h"
#include <Dogo.h>
#include "Dogo/Core.h"
#include "Dogo/LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Dogo/Events/Event.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#include "Dogo/Renderer/Camera.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Dogo/Timer.h"
#include "Dogo/DogoMemory.h"
#include "Dogo/Physics/DG_Physics.h"
#include "DogoECS.h"
#include "Dogo/Component/Component.h"
//#include "Dogo/Actors/Actor.h"
#include "Dogo/Renderer/Line.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/DogoWindow.h"
#include "AppLayer.h"
class Sandbox : public Dogo::Application
{
public:

	bool OnWindowClose(Dogo::WindowCloseEvent& e)
	{
		return Application::OnWindowClose(e);
	}
	bool KeyPressedCallBack(Dogo::KeyPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool KeyReleasedCallBack(Dogo::KeyReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseMovedCallBack(Dogo::MouseMovedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseButtonPressedCallBack(Dogo::MouseButtonPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseButtonReleasedCallBack(Dogo::MouseButtonReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseScrolledCallBack(Dogo::MouseScrolledEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}


	Sandbox() : Application()
	{
		DG_TRACE("Hello Window");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Sandbox::OnEvent));
		AppLayer* layer = new AppLayer();
		PushLayer(layer);

		Dogo::MemoryUsage::PrintUsage();
		DogoECS::Init();
		Dogo::DG_Physics::InitPhysics(glm::vec3(0.0f, -9.81f, 0.0f));
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::BaseComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::DynamicMeshComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::TransformComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::StaticMeshComponent>();

		Dogo::Renderer2D* Renderer = Dogo::Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl");
		layer->Renderer = Renderer;
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
		//Dogo::Texture* lebron = Dogo::Texture::Create("../Dogo/resources/Textures/lebron.png", "legacy", Dogo::TextureType::twoD, "lebron");
		//Dogo::Texture* rat = Dogo::Texture::Create("..Dogo/resources/Textures/rat.png", "legacy", Dogo::TextureType::twoD, "rat");
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		Renderer->LoadFont("../Dogo/resources/Fonts/arial.ttf", 48);
		static constexpr int NUM_ROWS = 100;
		static constexpr int NUM_COLS = 100;
		static constexpr float QUAD_SIZE = 5.0f;
		static constexpr float PADDING = 2.0f;
		std::shared_ptr<Dogo::DogoUI::UIButton> button = std::make_shared<Dogo::DogoUI::UIButton>();
		std::shared_ptr<Dogo::DogoUI::UIPanel> panel = std::make_shared<Dogo::DogoUI::UIPanel>();
		Dogo::DogoUI::AddElement(panel);
		button->visible = true;
		panel->visible = true;
		panel->color = { 1.0f, 0.0f, 1.0f };
		panel->size = { 1280.0f / 2, 720.0f / 2 };
		panel->pos = { 0.0f, 0.0f };
		button->text = "Click Me!";
		button->pos = { panel->pos.x / 2 - 50.0f,  panel->pos.y / 2 };
		button->size = { 200.0f, 60.0f };
		button->color = { 0.0f, 1.0f, 0.0f };
		button->onClick = []() { DG_INFO("Button Clicked!"); };
		panel->AddElement(button);


	}
	~Sandbox()
	{

	}

	void OnEvent(Dogo::Event& e) override
	{
		Dogo::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Dogo::WindowCloseEvent>(DG_BIND_EVENT_FN(Sandbox::OnWindowClose));
		//dispatcher.Dispatch<Dogo::KeyPressedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyPressedCallBack));
		//dispatcher.Dispatch<Dogo::KeyReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseMovedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseMovedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonPressedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonPressedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseScrolledEvent>(DG_BIND_EVENT_FN(Sandbox::MouseScrolledCallBack));
	}


};

Dogo::Application* Dogo::CreateApplication()
{
	return new Sandbox();
}