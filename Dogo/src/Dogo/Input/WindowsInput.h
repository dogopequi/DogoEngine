#pragma once
#include "Input.h"
namespace Dogo
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int32_t keycode) override;

		virtual bool IsMouseButtonPressedImpl(int32_t button) override;
		virtual void ProcessKeyImpl(int32_t key, bool pressed) override;
		virtual void ProcessButtonImpl(int32_t button, bool pressed) override;
		virtual void ProcessMousePosImpl(std::pair<int32_t, int32_t> mousepos) override;
		virtual void ProcessMouseScrollImpl(std::pair<int32_t, int32_t> scroll) override;
		virtual void ProcessScrollDeltaImpl(int32_t delta) override;
	};
}

