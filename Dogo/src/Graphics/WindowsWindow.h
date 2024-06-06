#pragma once
#if DG_PLATFORM_WINDOWS
#include "Window.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Core.h"

namespace Dogo
{
	LRESULT CALLBACK Win32ProcessMessage(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam);
	class DG_API WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowAttrib& attrib);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		void WindowSleep(float ms) const override;
		float GetClock() const override;
		void SetVsync(bool b) override;
		bool isVSync() const { return m_VSync; }
		HWND GetHandle() { return m_Hwnd; }
		bool WindowsMessages();
		bool InitContext() override;
		bool isRunning() const override { return m_IsRunning; }
		inline void SetInstance(HINSTANCE instance) { m_Instance = instance; }
		bool Init() override;
		void SetEventCallback(const EventCallbackFn& callback) override { EventCallback = callback; }
		void ClearColor(float x, float y, float z, float a) override;
		EventCallbackFn GetEventCallback() const { return EventCallback; }
		GraphicsContext* GetContext() const override { return m_Context; }

		void StopRunning() { m_IsRunning = false; }

		void LockCursor();
		void UnlockCursor();
	private:
		virtual void Shutdown();
	private:
		uint32_t m_Width{};
		uint32_t m_Height{};
		std::string m_Name{};
		bool m_VSync{};
		bool m_IsRunning;
		//Windows stuff
		HINSTANCE m_Instance{};
		HWND m_Hwnd{};
		uint32_t x = 500;
		uint32_t y = 300;
		GraphicsContext* m_Context;
		static std::map<HWND, WindowsWindow*> s_Handles;
		EventCallbackFn EventCallback;
		WindowAttrib m_Data;


	public:
		static WindowsWindow* GetWindowClass(HWND handle);
		static void RegisterWindowClass(HWND handle, WindowsWindow* window);
	};
}
#endif