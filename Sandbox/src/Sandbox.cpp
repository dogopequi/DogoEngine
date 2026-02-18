#include "dgpch.h"
#include "Sandbox.h"
#include "Dogo/Core.h"
#include "Dogo/App/LayerStack.h"
#include "Dogo/App/Layer.h"
#include "Platform/OpenGL/Shader.h"
#include "Dogo/Events/Event.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "Platform/OpenGL/Texture2D.h"
#include "Dogo/Utils/Timer.h"
#include "Dogo/Utils/DogoMemory.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Platform/OpenGL/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/Window.h"
#include "Examples/Pong.h"
#include "Examples/Snake.h"


	void Sandbox::Tick()
	{
	}

	Sandbox::Sandbox() : Application()
	{
		//Pong* pong = new Pong(m_Renderer);
		//pong->window = m_Window;
		//pong->OnAttach();
		//PushLayer(pong);
		SnakeGame* snake = new SnakeGame("Snake", m_Window);
		PushLayer(snake);
	}
