#include "dgpch.h"
#include <Dogo.h>

class Sandbox : public Dogo::Application
{
public:
	Sandbox()
	{
		DG_INFO("Hello Window");
	}
	~Sandbox()
	{

	}


};

Dogo::Application* Dogo::CreateApplication()
{
	return new Sandbox();
}