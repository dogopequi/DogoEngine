#include "dgpch.h"
#include "Sandbox.h"
#include "Dogo/Core.h"
#include "Dogo/LayerStack.h"
#include "Dogo/Layer.h"
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
#include "Dogo/Renderer/Line.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/DogoWindow.h"
#include "Examples/Pong.h"


	void Sandbox::Tick()
	{
	}

	Sandbox::Sandbox() : Application()
	{
		DG_TRACE("Hello Window");
		Pong* pong = new Pong(m_Renderer);
		pong->window = m_Window;
		pong->OnAttach();
		PushLayer(pong);
	}
