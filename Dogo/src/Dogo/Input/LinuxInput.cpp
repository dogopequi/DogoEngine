#include "dgpch.h"
#if DG_PLATFORM_LINUX
#include "LinuxInput.h"
#include "Graphics/LinuxWindow.h"

namespace Dogo
{
    	bool LinuxInput::IsKeyPressedImpl(int32_t keycode) 
        {
            LinuxWindow* LinuxW = LinuxWindow::GetWindowClass(nullptr);
            char keys[32];
            XQueryKeymap(LinuxW->GetDisplay(), keys);

            int byteIndex = keycode / 8;
            int bitIndex = keycode % 8;

            if((keys[byteIndex] & (1 << bitIndex)) != 0)
                return true;
            return false;
        }

		bool LinuxInput::IsMouseButtonPressedImpl(int32_t button)
        {
            LinuxWindow* LinuxW = LinuxWindow::GetWindowClass(nullptr);
            Window root_return, child_return;
            int root_x, root_y, win_x, win_y;
            unsigned int mask_return;

            XQueryPointer(LinuxW->GetDisplay(), LinuxW->GetRoot(), &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask_return);

            if((mask_return & button) != 0)
                return true;
            return false;
        }
		void LinuxInput::ProcessKeyImpl(int32_t key, bool pressed)
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
		void LinuxInput::ProcessButtonImpl(int32_t button, bool pressed)
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
		void LinuxInput::ProcessMousePosImpl(std::pair<int32_t, int32_t> mousepos)
        {
        if (mousepos != Input::GetMousePosition())
		{
			Input::SetMousePos(mousepos);
			return;
		}
        }
		void LinuxInput::ProcessMouseScrollImpl(std::pair<int32_t, int32_t> scroll)
        {
        if (scroll != Input::GetMouseScroll())
		{
			Input::SetScroll(scroll);
		}
        }
		void LinuxInput::ProcessScrollDeltaImpl(int32_t delta)
        {
        if (delta != Input::GetScrollDelta())
		{
			Input::SetScrollDelta(delta);
		}
        }
}




#endif