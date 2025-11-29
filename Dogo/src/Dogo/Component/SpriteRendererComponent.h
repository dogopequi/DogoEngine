#pragma once
#include "Components.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Renderer/2D/Sprite.h"
namespace Dogo
{
	namespace ECS
	{
		struct SpriteRendererComponent : public DogoECS::DG_Component
		{
			SpriteRendererComponent() : DogoECS::DG_Component() {}
			Sprite sprite{};

			inline void Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY)
			{
				if (!renderer.expired()) {
					if (sprite.GetTexture().has_value())
					{
						//renderer.lock()->Submit(glm::vec2(actorX, actorY), glm::vec2(sprite.GetWidth(), sprite.GetHeight()), sprite.GetTexture().value());
						renderer.lock()->Submit(CreateQuad(actorX, actorY, sprite.GetWidth(), sprite.GetHeight(), sprite.GetPivotX(), sprite.GetPivotY(), sprite.GetUV()), sprite.GetTexture().value());
					}
				}
				else
					DG_ERROR("Renderer pointer in Sprite: %s has expired.", sprite.GetName());
			}
			//layer
			//layer id
		};
	}
}