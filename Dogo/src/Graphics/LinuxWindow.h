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
			GraphicsContext::Create(RenderAPI::OpenGL, display, visual, screen, window);
			m_Context = GraphicsContext::Get();
			if (!m_Context->Init())
				return false;

			return true;
		}
		virtual bool isRunning() const override{ return m_IsRunning;}
		virtual bool Init() override{return true;}
		virtual void ClearColor(float x, float y, float z, float a) override{m_Context->ClearColor(x, y, z, a);}
		virtual void SetEventCallback(const EventCallbackFn& callback) override;
		virtual GraphicsContext* GetContext() const override{return m_Context;}

		inline Display* GetDisplay() const {return display;}
		inline Window GetRoot() const {return root;}
		EventCallbackFn GetEventCallback() const { return EventCallback; }

	private:
		virtual bool Init(const WindowAttrib& attrib);
		virtual void Shutdown();
	private:
		uint32_t m_Width{};
		uint32_t m_Height{};
		std::string m_Name{};
		bool m_VSync{};
		bool m_IsRunning = false;
		Display* display = nullptr;
		int screen;
		Window root;
		Window window;
		XEvent event;
		Visual* visual = nullptr;
		Colormap colormap;
		GraphicsContext* m_Context = nullptr;
		EventCallbackFn EventCallback;

		static std::map<const char* , LinuxWindow*> s_Handles;

		public:
		static LinuxWindow* GetWindowClass(const char* handle);
		static void RegisterWindowClass(const char* handle, LinuxWindow* window);

	};
}

#endif

