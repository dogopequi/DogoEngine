#pragma once
//#include <tchar.h>
#if DG_PLATFORM_WINDOWS
#include "Dogo/Input/WindowsInput.h"
#endif
#if DG_PLATFORM_LINUX
#include "Dogo/Input/LinuxInput.h"
#endif
extern Dogo::Application* Dogo::CreateApplication();

//#if DG_PLATFORM_WINDOWS
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//	// Allocate a new console window
//	AllocConsole();
//
//	// Redirect stdout to the new console
//	freopen("CONOUT$", "w", stdout);
//	auto app = Dogo::CreateApplication();
//	app->SetWindowsInstance(hInstance);
//	app->Run();
//	delete app;
//}
//#endif
//#if DG_PLATFORM_LINUX
#if DG_PLATFORM_WINDOWS
Dogo::Input* Dogo::Input::s_Instance = new Dogo::WindowsInput();
#else
Dogo::Input* Dogo::Input::s_Instance = new Dogo::LinuxInput();
#endif
int main(int argc, char** argv)
{
//    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    DWORD dwMode = 0;
//    GetConsoleMode(hOut, &dwMode);
//    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//    SetConsoleMode(hOut, dwMode);
	auto app = Dogo::CreateApplication();
	app->Run();
	// delete app;
}
//#endif
