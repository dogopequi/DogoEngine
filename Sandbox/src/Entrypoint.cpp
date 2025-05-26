#include "dgpch.h"
#include <Dogo.h>
#include "Sandbox.h"
#ifdef DG_SANDBOX_MODE_APP
Dogo::Application* Dogo::CreateApplication()
{
	return new Sandbox();
}
#endif