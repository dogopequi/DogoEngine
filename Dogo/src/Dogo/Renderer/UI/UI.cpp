#include "dgpch.h"
#include "UI.h"
namespace Dogo
{
	namespace DogoUI
	{
		void UIButton::Draw(Renderer2D* renderer, const glm::mat4 parentTransform)
		{
			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
			renderer->Push(transform);

			renderer->Submit(CreateRoundedRect(
				{ 0.0f, 0.0f }, 
				size,            
				90.0f,           
				{ 1.0f, 0.0f, 0.0f, 1.0f },
				0.0f
			));

			renderer->RenderText(text, 0.0f, 0.0f, 0.5f,
				hovered ? glm::vec3(1.0f, 1.0f, 0.0f) : glm::vec3(1.0f));

			renderer->Pop();
		}
		bool UIButton::MouseHandler(const glm::vec2& mousePos, bool isPressed, const glm::mat4 parentTransform)
		{
			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
			glm::vec2 localMouse = glm::vec2(glm::inverse(transform) * glm::vec4(mousePos, 0.0f, 1.0f));

			hovered = (localMouse.x >= 0 && localMouse.x <= size.x &&
				localMouse.y >= 0 && localMouse.y <= size.y);

			if (hovered)
			{
				if (isPressed)
				{
					pressed = true;
				}
				else if (pressed)
				{
					pressed = false;
					if (onClick) onClick();
				}
			}
			else
			{
				pressed = false;
			}

			return hovered;
		}
	}
}