#pragma once
#include "Dogo/Renderer/2D/Renderer2D.h"
namespace Dogo
{

	namespace SpriteRenderSystem2D
	{
		void Update(const std::weak_ptr<Renderer2D>& renderer);
	}

	namespace PhysicsSystem
	{
		void Update(double step);
	};

	namespace AudioSystem2D
	{
		void Update();
	}
	namespace AudioSystem3D
	{
		void Update();
	}
	namespace MovementSystem2D
	{
		void Update(double step);
	}
	namespace MovementSystem3D
	{
		void Update(double step);
	}
}