#pragma once

#if DG_PLATFORM_LINUX
#include "Window.h"
//#include <xcb/xcb.h>
//#include <X11/keysym.h>
//#include <X11/XKBlib.h>
//#include <X11/Xlib.h>
//#include <X11/Xlib-xcb.h>
//#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif


namespace Dogo
{
	struct LinuxState
	{
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wmProtocols;
		xcb_atom_t wmDelete_win;
	};
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
		
		
		virtual bool InitContext() override {}
		virtual bool isRunning() const override{}
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
		LinuxState state{};

	};
}

#endif

