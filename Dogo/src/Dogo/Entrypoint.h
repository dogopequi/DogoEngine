#pragma once
#include "Dogo/Application.h"
//#include <tchar.h>
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
//#if DG_PLATFORM_WINDOWS
//Dogo::Input* = new Dogo::Input();
//#else
//Dogo::Input* Dogo::Input::s_Instance = new Dogo::LinuxInput();
//#endif
int main(int argc, char** argv)
{
	auto app = Dogo::CreateApplication();
	app->Run();
	delete app;
}
//#endif
//