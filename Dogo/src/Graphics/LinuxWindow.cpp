#include "dgpch.h"
#include "LinuxWindow.h"
#if DG_PLATFORM_LINUX
#include "Dogo/Core.h"
#include "Dogo/Logger.h"
namespace Dogo
{
	DG_Window* DG_Window::Create(const WindowAttrib& attrib)
	{
		return new LinuxWindow(attrib);
	}
	
	LinuxWindow::LinuxWindow(const WindowAttrib& attrib)
	{
		Init(attrib);
	}
	
	LinuxWindow::~LinuxWindow()
	{
		Shutdown();
	}
	
	bool LinuxWindow::Init(const WindowAttrib& attrib)
	{
		state.display = XOpenDisplay(NULL);
		
		XAutoRepeatOff(state.display);
	}
	
	void LinuxWindow::Shutdown()
	{
		
	}
	
	void LinuxWindow::OnUpdate()
	{
		
	}
	
	void LinuxWindow::WindowSleep(float ms) const
	{
		
	}
	
	float LinuxWindow::GetClock() const
	{
		
	}
	
	void LinuxWindow::SetVsync(bool b)
	{
		
	}

	//TODO
}
#endif