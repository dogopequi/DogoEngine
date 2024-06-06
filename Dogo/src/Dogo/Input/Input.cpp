#include "dgpch.h"
#include "Input.h"
namespace Dogo
{
	//Input* Input::s_Instance;
	std::pair<int32_t, int32_t> Input::m_Scroll;
	int32_t Input::m_ScrollDelta;
	std::pair<int32_t, int32_t> Input::m_MousePosition;
	int32_t Input::m_Key;
	int32_t Input::m_Button;
	std::pair<int32_t, int32_t> Input::m_LastMousePosition;
	int32_t Input::m_LastKey;
	int32_t Input::m_LastButton;
	KeyState Input::m_KeyState;
	ButtonState Input::m_ButtonState;
}