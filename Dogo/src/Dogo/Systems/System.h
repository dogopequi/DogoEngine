#pragma once
#include "Platform/OpenGL/Renderer2D.h"
namespace Dogo
{

	namespace SpriteRenderSystem2D
	{
		constexpr const size_t MaxLayers = 16;
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