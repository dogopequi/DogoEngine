#pragma once

#include "Event.h"

namespace Dogo {

	class DG_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int32_t x, int32_t y)
			: m_MouseX(x), m_MouseY(y) {}

		inline int32_t GetX() const { return m_MouseX; }
		inline int32_t GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		int32_t m_MouseX, m_MouseY;
	};

	class DG_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int32_t xOffset, int32_t yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline int32_t GetXOffset() const { return m_XOffset; }
		inline int32_t GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		int32_t m_XOffset, m_YOffset;
	};

	class DG_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class DG_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, bool isRepeated)
			: MouseButtonEvent(button), m_IsRepeated(isRepeated) {}

		inline bool IsRpeated() const { return m_IsRepeated; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button << " : " << ButtonCodeToButtonName(m_Button) << " (" << (m_IsRepeated ? "Is Repeated" : "Not Repeated") << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		bool m_IsRepeated;

	};

	class DG_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}