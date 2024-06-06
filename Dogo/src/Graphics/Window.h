#pragma once

#include "Dogo/Core.h"
#include "Dogo/Events/Event.h"
#include "Graphics/GraphicsContext.h"
namespace Dogo
{

	struct WindowAttrib
	{
		std::string Name;
		uint32_t Width;
		uint32_t Height;

		WindowAttrib(const std::string& name = "Dogo Engine", uint32_t width = 1280, uint32_t height = 720)
			: Name(name), Width(width), Height(height){}
	};
	class DG_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		virtual void WindowSleep(float ms) const = 0;
		virtual float GetClock() const = 0;
		virtual void SetVsync(bool b) = 0;
		virtual bool isVSync() const = 0;
		virtual bool InitContext() = 0;
		virtual bool isRunning() const = 0;
		virtual bool Init() = 0;
		virtual void ClearColor(float x, float y, float z, float a) = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual GraphicsContext* GetContext() const = 0;
#if DG_PLATFORM_WINDOWS
		virtual void SetInstance(HINSTANCE instance) = 0;
#endif

		static Window* Create(const WindowAttrib& attrib = WindowAttrib());
	};
}

