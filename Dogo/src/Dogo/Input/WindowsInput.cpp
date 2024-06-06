#include "dgpch.h"
#include "WindowsInput.h"
#include "Graphics/WindowsWindow.h"
namespace Dogo
{
	bool WindowsInput::IsKeyPressedImpl(int32_t keycode)
	{
		if (GetAsyncKeyState(keycode))
			return true;

		return false;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int32_t button)
	{
		if (GetAsyncKeyState(button))
			return true;

		return false;
	}

	void WindowsInput::ProcessKeyImpl(int32_t key, bool pressed)
	{
		bool same = true;
		if (key != Input::GetKey()) { same = false; }
		if(!same)
		{
			if (pressed) // repeat
			{
				Input::SetKey(key);
				Input::SetKeyState(KeyState::PRESSED);
				return;
			}
		}
		if(same)
		{
			if (pressed) // repeat
			{
				Input::SetKey(key);
				Input::SetKeyState(KeyState::REPEAT);
				return;
			}
			else
			{
				Input::SetKeyState(KeyState::RELEASED);
				return;
			}
		}
	}
	void WindowsInput::ProcessButtonImpl(int32_t button, bool pressed)
	{
		bool same = true;
		if (button != Input::GetButton()) { same = false; }
		if (!same)
		{
			if (pressed) // repeat
			{
				Input::SetButton(button);
				Input::SetButtonState(ButtonState::PRESSED);
				return;
			}
		}
		if (same)
		{
			if (pressed) // repeat
			{
				Input::SetButton(button);
				Input::SetButtonState(ButtonState::REPEAT);
				return;
			}
			else
			{
				Input::SetButtonState(ButtonState::RELEASED);
				return;
			}
		}
	}

	void WindowsInput::ProcessMousePosImpl(std::pair<int32_t, int32_t> mousepos)
	{
		if (mousepos != Input::GetMousePosition())
		{
			Input::SetMousePos(mousepos);
			return;
		}
	}
	void WindowsInput::ProcessMouseScrollImpl(std::pair<int32_t, int32_t> scroll)
	{
		if (scroll != Input::GetMouseScroll())
		{
			Input::SetScroll(scroll);
		}
	}
	void WindowsInput::ProcessScrollDeltaImpl(int32_t delta)
	{
		if (delta != Input::GetScrollDelta())
		{
			Input::SetScrollDelta(delta);
		}
	}
}