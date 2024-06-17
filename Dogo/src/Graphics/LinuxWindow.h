#pragma once

#if DG_PLATFORM_LINUX
#include "Window.h"
#include <glad/gl.h>
#include <glad/glx.h>


#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif


namespace Dogo
{
	class DG_API LinuxWindow : public DG_Window
	{
	public:
		LinuxWindow(const WindowAttrib& attrib);
		virtual ~LinuxWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual void WindowSleep(float ms) const override;
		virtual float GetClock() const override;
		virtual void SetVsync(bool b) override;
		virtual bool isVSync() const { return m_VSync; }
		
		
		virtual bool InitContext() override 
		{ 
			GraphicsContext::Create(RenderAPI::OpenGL, display, vi);
			m_Context = GraphicsContext::Get();
			if (!m_Context->Init())
				return false;

			return true;
		}
		virtual bool isRunning() const override{ return m_IsRunning;}
		virtual bool Init() override{}
		virtual void ClearColor(float x, float y, float z, float a) override{}
		virtual void SetEventCallback(const EventCallbackFn& callback) override{}
		virtual GraphicsContext* GetContext() const override{}

	private:
		virtual bool Init(const WindowAttrib& attrib);
		virtual void Shutdown();
	private:
		uint32_t m_Width{};
		uint32_t m_Height{};
		std::string m_Name{};
		bool m_VSync{};
		bool m_IsRunning = false;
		Display* display;
		int screen;
		Window root;
		Window window;
		XEvent event;
		Visual* visual;
		GraphicsContext* m_Context;

	};
}

#endif

