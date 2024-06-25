#include "dgpch.h"
#include <Dogo.h>

class Sandbox : public Dogo::Application
{
public:
	Sandbox()
	{
		DG_TRACE("Hello Window");
	}
	~Sandbox()
	{

	}


};

Dogo::Application* Dogo::CreateApplication()
{
	return new Sandbox();
}