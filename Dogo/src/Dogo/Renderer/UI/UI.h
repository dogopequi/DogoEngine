#pragma once
#include "glm/common.hpp"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Logger.h"
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
			virtual void Draw(std::shared_ptr<Renderer2D> renderer, const glm::mat4 parentTransform) = 0;
			virtual bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform, const Viewport& viewport) = 0;
			virtual bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform) = 0;
		};

		struct UIButton : public UIElement
		{
			std::string text;
			std::function<void()> onClick;
			bool hovered = false;
			uint32_t button;

			void Draw(std::shared_ptr<Renderer2D> renderer, const glm::mat4 parentTransform) override;
			bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform, const Viewport& viewport) override;
			bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform) override;
		};

		struct UIPanel : public UIElement
		{
			std::deque<std::shared_ptr<UIElement>> children;
			inline void Draw(std::shared_ptr<Renderer2D> renderer, const glm::mat4 parentTransform) override
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
			inline bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform, const Viewport& viewport) override
			{
				glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
				glm::vec2 localMouse = mousePos - pos;
				if (localMouse.x >= 0 && localMouse.x <= size.x &&
					localMouse.y >= 0 && localMouse.y <= size.y)
				{
					for (auto& element : children)
					{
						if (element->MouseHandler(localMouse, transform, viewport))
						{
							return true;
						}
					}
				}
				return false;
			}
			inline bool MouseHandler(const glm::vec2& mousePos, const glm::mat4 parentTransform) override
			{
				glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
				glm::vec2 localMouse = glm::vec2(glm::inverse(transform) * glm::vec4(mousePos, 0.0f, 1.0f));
				for (auto& element : children) {
					if (element->MouseHandler(localMouse, transform)) {
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

		inline bool UseViewport = false;
		inline glm::vec2 WindowSize = {};
		inline std::deque<std::shared_ptr<UIPanel>> m_GameUIPanels;
		inline std::deque<std::shared_ptr<UIPanel>> m_EditorUIPanels;
		inline glm::vec2 MousePosition;
		inline void UIAddGamePanel(std::shared_ptr<UIPanel> element)
		{
			m_GameUIPanels.push_front(element);
		}
		inline void UIAddEditorPanel(std::shared_ptr<UIPanel> element)
		{
			m_EditorUIPanels.push_front(element);
		}
		inline void HandleViewportInput(const Viewport& viewport)
		{
			if (UseViewport && viewport.visible)
			{
				glm::vec2 localMouse = MousePosition - viewport.pos;

				if (localMouse.x < 0 || localMouse.y < 0 ||
					localMouse.x > viewport.size.x || localMouse.y > viewport.size.y)
					return;
				glm::vec2 framebufferMouse = localMouse * (viewport.framebufferSize / viewport.size);
				glm::mat4 root = glm::mat4(1.0f);

				for (auto& element : m_GameUIPanels) {
					if (element->visible) {
						element->MouseHandler(framebufferMouse, root, viewport);
					}
				}
			}
		}

		inline void UIHandleGameInput()
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_GameUIPanels) {
				if (element->visible) {
					element->MouseHandler(MousePosition, root);
				}
			}
		}
		inline void UIHandleEditorInput()
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_EditorUIPanels) {
				if (element->visible) {
					element->MouseHandler(MousePosition, root);
				}
			}
		}

		inline void UIRenderGameElements(std::shared_ptr<Renderer2D> renderer)
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_GameUIPanels) {
				if (element->visible) {
					element->Draw(renderer, root);
				}
			}
			glDepthFunc(GL_ALWAYS);
			renderer->Flush();
		}
		inline void UIRenderEditorElements(std::shared_ptr<Renderer2D> renderer)
		{
			glm::mat4 root = glm::mat4(1.0f);
			for (auto& element : m_EditorUIPanels) {
				glEnable(GL_SCISSOR_TEST);
				glScissor(
					element->pos.x,
					WindowSize.y - element->pos.y - element->size.y,
					element->size.x,
					element->size.y
				);

				if (element->visible) {
					element->Draw(renderer, root);
				}
			}
			glDisable(GL_SCISSOR_TEST);
			glDepthFunc(GL_ALWAYS);
			renderer->Flush();
		}

		inline void DrawViewport(const Viewport& viewport, std::shared_ptr<Renderer2D> renderer, const glm::mat4 parentTransform)
		{
			glm::mat4 transform = parentTransform * glm::translate(glm::mat4(1.0f), glm::vec3(viewport.pos, 0.0f));
			renderer->Push(transform);
			renderer->DrawFrameBuffer(CreateQuad(
				0.0f,
				0.0f,
				glm::vec4(viewport.color, 1.0f),
				viewport.size.x,
				viewport.size.y,
				1.0f
			));
			renderer->Pop();
		}
	}
}