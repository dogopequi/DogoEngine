#include "dgpch.h"
#include "UI.h"
#include "Dogo/Utils/Logger.h"
#include "Dogo/Input/Input.h"
namespace Dogo
{
	namespace DogoUI
	{
		void UIButton::Draw(std::shared_ptr<Renderer2D> renderer, const glm::mat4 parentTransform)
		{
			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
			renderer->Push(transform);
			//renderer->Submit(CreateQuad(
			//	1.0f,
			//	1.0f,
			//	glm::vec4(color, 0.1f),
			//	size.x - 2.0f,
			//	size.y - 2.0f, 0, 0,
			//	0.0f
			//));
			//renderer->Submit(CreateQuad(
			//	0.0f,
			//	0.0f,
			//	glm::vec4(color, 1.0f),
			//	size.x,
			//	size.y, 0, 0,
			//	0.0f
			//));
			float textWidth = renderer->ComputeTextWidth(text, 0.5f);
			float textHeight = renderer->GetFontHeight(0.5f);

			glm::vec2 textPos = {
				(size.x - textWidth) / 2.0f,
				(size.y - textHeight) / 2.0f
			};
			renderer->SubmitText(text, textPos.x, textPos.y, 0.7f, hovered ? glm::vec3(1.0f, 1.0f, 0.0f) : glm::vec3(1.0f));


			renderer->Pop();
		}
		bool UIButton::MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform, const Viewport& viewport)
		{
			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
			glm::vec2 localMouse = mousePos - pos;
			hovered = (localMouse.x >= 0 && localMouse.x <= size.x &&
				localMouse.y >= 0 && localMouse.y <= size.y);
			bool isPressed = Dogo::Input::IsMouseButtonPressed(button);
			if (hovered)
			{
				if (isPressed)
				{
					if (onClick) onClick();
				}
			}

			return hovered;
		}

		bool UIButton::MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform)
		{

			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
			glm::vec2 localMouse = glm::vec2(glm::inverse(transform) * glm::vec4(mousePos, 0.0f, 1.0f));
			hovered = (localMouse.x >= 0 && localMouse.x <= size.x &&
				localMouse.y >= 0 && localMouse.y <= size.y);
			bool isPressed = Dogo::Input::IsMouseButtonPressed(button);
			if (hovered)
			{
				if (isPressed)
				{
					if (onClick) onClick();
				}
			}

			return hovered;
		}
	}
}