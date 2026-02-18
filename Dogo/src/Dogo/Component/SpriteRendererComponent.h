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
			uint32_t layer{ 0 };
			glm::vec4 color{ 0.0f,0.0f, 0.0f, 0.0f };
			inline void Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY)
			{
				if (!renderer.expired()) {
					if (sprite.IsUsingTexture())
						renderer.lock()->Submit(CreateQuad(actorX, actorY, sprite.GetWidth(), sprite.GetHeight(), sprite.GetPivotX(), sprite.GetPivotY(), sprite.GetUV()), sprite.GetTextureID());
					else
						renderer.lock()->Submit(CreateQuad(actorX, actorY, sprite.GetWidth(), sprite.GetHeight(), sprite.GetPivotX(), sprite.GetPivotY(), sprite.GetUV()), color);
				}
				else
					DG_ERROR("Renderer pointer in Sprite: %s has expired.", sprite.GetName());
			}
		};
	}
}