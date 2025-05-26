#pragma once
#include "glm/common.hpp"
#include "Dogo/Renderer/Renderer2D.h"
namespace Dogo
{
	namespace DogoUI
	{
		struct UIElement
		{
			glm::vec2 pos;
			glm::vec2 size;
			glm::vec3 color;
			bool transparent;
			bool visible = true;
			virtual void Draw(Renderer2D* renderer, const glm::mat4 parentTransform = glm::mat4(1.0f)) = 0;
			virtual bool MouseHandler(const glm::vec2& mousePos, bool isPressed, const glm::mat4 parentTransform = glm::mat4(1.0f)) = 0;
		};

		struct UIViewport : public UIElement
		{
			void Draw(Renderer2D* renderer, const glm::mat4 parentTransform) override
			{
				glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
				renderer->Push(transform);
				renderer->DrawFrameBuffer(CreateQuad(
					0.0f,
					0.0f,
					glm::vec4(color, 1.0f),
					size.x,
					size.y,
					0.0f
				));
				renderer->Pop();
			}

			bool MouseHandler(const glm::vec2& mousePos, bool isPressed, const glm::mat4 parentTransform) override
			{
				return false; // TODO
			}
		};

		struct UIButton : public UIElement
		{
			std::string text;
			std::function<void()> onClick;
			bool hovered = false;

			void Draw(Renderer2D* renderer, const glm::mat4 parentTransform) override;
			bool MouseHandler(const glm::vec2& mousePos, bool isPressed, const glm::mat4 parentTransform) override;
		};

		struct UIPanel : public UIElement
		{
			std::deque<std::shared_ptr<UIElement>> children;
			inline void Draw(Renderer2D* renderer, const glm::mat4 parentTransform) override
			{
				glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
				renderer->Push(transform);
				for (auto& child : children)
				{
					if(child->visible)
						child->Draw(renderer, transform);
				}
				renderer->Submit(CreateQuad(
					0.0f,
					0.0f,
					glm::vec4(color, 0.5f),
					size.x,
					size.y,
					0.0f
				));
				renderer->Pop();
			}
			inline bool MouseHandler(const glm::vec2& mousePos, bool isPressed, const glm::mat4 parentTransform) override
			{
				glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
				for (auto& element : children) {
					if (element->MouseHandler(mousePos, isPressed, parentTransform)) {
						return true;
					}
				}
				return false;
			}
			inline void AddElement(std::shared_ptr<UIElement> element)
			{
				children.push_front(element);
			}
		};


		inline std::deque<std::shared_ptr<UIElement>> m_Elements;

		inline void AddElement(std::shared_ptr<UIElement> element)
		{
			m_Elements.push_front(element);
		}
		inline void HandleInput(const glm::vec2& mousePos, bool isPressed)
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_Elements) {
				if (element->visible) {
					element->MouseHandler(mousePos, isPressed, root);
				}
			}
		}

		inline void Render(Renderer2D* renderer)
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_Elements) {
				if (element->visible) {
					element->Draw(renderer, root);
				}
			}
			glDepthFunc(GL_ALWAYS);
			renderer->Flush();
		}

	}
}