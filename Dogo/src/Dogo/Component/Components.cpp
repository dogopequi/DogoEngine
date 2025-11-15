#include "dgpch.h"
#include "Components.h"
#include "Dogo/Renderer/2D/Sprite.h"
namespace Dogo
{
	SpriteRendererComponent::SpriteRendererComponent() : DG_Component()
	{

	}

	void SpriteRendererComponent::Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY)
	{
		Texture* t = sprite.GetTexture();
		if (t == nullptr)
			return;
		if (!renderer.expired()) {
			renderer.lock()->Submit(CreateQuad(actorX, actorY, glm::vec4(0.0f), sprite.GetWidth(), sprite.GetHeight(), sprite.GetPivotX(), sprite.GetPivotY(), t->GetID()), t);
		}
		else
			DG_ERROR("Renderer pointer in Sprite: %s has expired.", sprite.GetName());
	}
}