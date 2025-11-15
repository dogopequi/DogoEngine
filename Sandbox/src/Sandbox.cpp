#include "dgpch.h"
#include "Sandbox.h"
#include "Dogo/Core.h"
#include "Dogo/App/LayerStack.h"
#include "Dogo/App/Layer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Dogo/Events/Event.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#include "Dogo/Renderer/Camera.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Core/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Dogo/Utils/Timer.h"
#include "Dogo/Utils/DogoMemory.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Renderer/3D/Line.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/DogoWindow.h"
#include "Examples/Pong.h"
#include "Examples/Test.h"


	void Sandbox::Tick()
	{
	}

	Sandbox::Sandbox() : Application()
	{
		DG_TRACE("Hello Window");
		//Pong* pong = new Pong(m_Renderer);
		//pong->window = m_Window;
		//pong->OnAttach();
		//PushLayer(pong);
		TestLayer* test = new TestLayer(m_Renderer);
		PushLayer(test);
	}
