#pragma once
#include "Dogo/Logger.h"

// TODO: Needs work to handle edge cases (combo input when using alt and shift) need a better solution


#define AMERICAN 0
// FOR US KEYBOARD
//#define DG_KEY_SPACE              32
//#define DG_KEY_APOSTROPHE         39
//#define DG_KEY_COMMA              44
//#define DG_KEY_MINUS              45
//#define DG_KEY_PERIOD             46
//#define DG_KEY_SLASH              47
//#define DG_KEY_0                  48
//#define DG_KEY_1                  49
//#define DG_KEY_2                  50
//#define DG_KEY_3                  51
//#define DG_KEY_4                  52
//#define DG_KEY_5                  53
//#define DG_KEY_6                  54
//#define DG_KEY_7                  55
//#define DG_KEY_8                  56
//#define DG_KEY_9                  57
//#define DG_KEY_SEMICOLON          59
//#define DG_KEY_EQUAL              61
//#define DG_KEY_A                  65
//#define DG_KEY_B                  66
//#define DG_KEY_C                  67
//#define DG_KEY_D                  68
//#define DG_KEY_E                  69
//#define DG_KEY_F                  70
//#define DG_KEY_G                  71
//#define DG_KEY_H                  72
//#define DG_KEY_I                  73
//#define DG_KEY_J                  74
//#define DG_KEY_K                  75
//#define DG_KEY_L                  76
//#define DG_KEY_M                  77
//#define DG_KEY_N                  78
//#define DG_KEY_O                  79
//#define DG_KEY_P                  80
//#define DG_KEY_Q                  81
//#define DG_KEY_R                  82
//#define DG_KEY_S                  83
//#define DG_KEY_T                  84
//#define DG_KEY_U                  85
//#define DG_KEY_V                  86
//#define DG_KEY_W                  87
//#define DG_KEY_X                  88
//#define DG_KEY_Y                  89
//#define DG_KEY_Z                  90
//#define DG_KEY_LEFT_BRACKET       91
//#define DG_KEY_BACKSLASH          92
//#define DG_KEY_RIGHT_BRACKET      93
//#define DG_KEY_GRAVE_ACCENT       96
//
//
//#define DG_KEY_ESCAPE             256
//#define DG_KEY_ENTER              257
//#define DG_KEY_TAB                258
//#define DG_KEY_BACKSPACE          259
//#define DG_KEY_INSERT             260
//#define DG_KEY_DELETE             261
//#define DG_KEY_RIGHT              262
//#define DG_KEY_LEFT               263
//#define DG_KEY_DOWN               264
//#define DG_KEY_UP                 265
//#define DG_KEY_PAGE_UP            266
//#define DG_KEY_PAGE_DOWN          267
//#define DG_KEY_HOME               268
//#define DG_KEY_END                269
//#define DG_KEY_CAPS_LOCK          280
//#define DG_KEY_SCROLL_LOCK        281
//#define DG_KEY_NUM_LOCK           282
//#define DG_KEY_PRINT_SCREEN       283
//#define DG_KEY_PAUSE              284
//#define DG_KEY_F1                 290
//#define DG_KEY_F2                 291
//#define DG_KEY_F3                 292
//#define DG_KEY_F4                 293
//#define DG_KEY_F5                 294
//#define DG_KEY_F6                 295
//#define DG_KEY_F7                 296
//#define DG_KEY_F8                 297
//#define DG_KEY_F9                 298
//#define DG_KEY_F10                299
//#define DG_KEY_F11                300
//#define DG_KEY_F12                301
//#define DG_KEY_F13                302
//#define DG_KEY_F14                303
//#define DG_KEY_F15                304
//#define DG_KEY_F16                305
//#define DG_KEY_F17                306
//#define DG_KEY_F18                307
//#define DG_KEY_F19                308
//#define DG_KEY_F20                309
//#define DG_KEY_F21                310
//#define DG_KEY_F22                311
//#define DG_KEY_F23                312
//#define DG_KEY_F24                313
//#define DG_KEY_F25                314
//#define DG_KEY_KP_0               320
//#define DG_KEY_KP_1               321
//#define DG_KEY_KP_2               322
//#define DG_KEY_KP_3               323
//#define DG_KEY_KP_4               324
//#define DG_KEY_KP_5               325
//#define DG_KEY_KP_6               326
//#define DG_KEY_KP_7               327
//#define DG_KEY_KP_8               328
//#define DG_KEY_KP_9               329
//#define DG_KEY_KP_DECIMAL         330
//#define DG_KEY_KP_DIVIDE          331
//#define DG_KEY_KP_MULTIPLY        332
//#define DG_KEY_KP_SUBTRACT        333
//#define DG_KEY_KP_ADD             334
//#define DG_KEY_KP_ENTER           335
//#define DG_KEY_KP_EQUAL           336
//#define DG_KEY_LEFT_SHIFT         340
//#define DG_KEY_LEFT_CONTROL       341
//#define DG_KEY_LEFT_ALT           342
//#define DG_KEY_LEFT_SUPER         343
//#define DG_KEY_RIGHT_SHIFT        344
//#define DG_KEY_RIGHT_CONTROL      345
//#define DG_KEY_RIGHT_ALT          346
//#define DG_KEY_RIGHT_SUPER        347
//#define DG_KEY_MENU               348

// FOR SPANISH US KEYBOARD
#define SPANISH 1
#define DG_KEY_SPACE              32
#define DG_KEY_APOSTROPHE         219
#define DG_KEY_COMMA              188
#define DG_KEY_MINUS              189
#define DG_KEY_PERIOD             190
#define DG_KEY_SLASH              DG_KEY_7 //DG_KEY_RIGHT_SHIFT
#define DG_KEY_0                  48
#define DG_KEY_1                  49
#define DG_KEY_2                  50
#define DG_KEY_3                  51
#define DG_KEY_4                  52
#define DG_KEY_5                  53
#define DG_KEY_6                  54
#define DG_KEY_7                  55
#define DG_KEY_8                  56
#define DG_KEY_9                  57
#define DG_KEY_SEMICOLON          DG_KEY_COMMA //DG_KEY_RIGHT_SHIFT
#define DG_KEY_COLON              DG_KEY_PERIOD //DG_KEY_RIGHT_SHIFT
#define DG_KEY_EQUAL              DG_KEY_0 //DG_KEY_RIGHT_SHIFT
#define DG_KEY_A                  65
#define DG_KEY_B                  66
#define DG_KEY_C                  67
#define DG_KEY_D                  68
#define DG_KEY_E                  69
#define DG_KEY_F                  70
#define DG_KEY_G                  71
#define DG_KEY_H                  72
#define DG_KEY_I                  73
#define DG_KEY_J                  74
#define DG_KEY_K                  75
#define DG_KEY_L                  76
#define DG_KEY_M                  77
#define DG_KEY_N                  78
#define DG_KEY_O                  79
#define DG_KEY_P                  80
#define DG_KEY_Q                  81
#define DG_KEY_R                  82
#define DG_KEY_S                  83
#define DG_KEY_T                  84
#define DG_KEY_U                  85
#define DG_KEY_V                  86
#define DG_KEY_W                  87
#define DG_KEY_X                  88
#define DG_KEY_Y                  89
#define DG_KEY_Z                  90
#define DG_KEY_GRAVE_ACCENT       186 // ` = [
#define DG_KEY_PLUS				  187// + = ]
#define DG_KEY_ACUTE_ACCENT       222 // ´ = {
#define DG_KEY_CEDILHA            191 // ç = }
#define DG_KEY_DEGREE             220 // º = \

#define DG_KEY_LEFT_BRACKET       186 // DG_KEY_RIGHT_ALT
#define DG_KEY_RIGHT_BRACKET      187 // DG_KEY_RIGHT_ALT
#define DG_KEY_LEFT_CURLY_BRACKET 222 // DG_KEY_RIGHT_ALT
#define DG_KEY_RIGHT_CURLY_BRACKET 191 // DG_KEY_RIGHT_ALT
#define DG_KEY_BACKSLASH          220 // DG_KEY_RIGHT_ALT
#define DG_KEY_ESCAPE             27
#define DG_KEY_ENTER              13
#define DG_KEY_TAB                9
#define DG_KEY_BACKSPACE          8
#define DG_KEY_INSERT             45
#define DG_KEY_DELETE             46
#define DG_KEY_RIGHT              39
#define DG_KEY_LEFT               37
#define DG_KEY_DOWN               40
#define DG_KEY_UP                 38
#define DG_KEY_PAGE_UP            34
#define DG_KEY_PAGE_DOWN          33
#define DG_KEY_HOME               36
#define DG_KEY_END                35
#define DG_KEY_CAPS_LOCK          20
#define DG_KEY_SCROLL_LOCK        145
#define DG_KEY_PRINT_SCREEN       44
#define DG_KEY_PAUSE              19
#define DG_KEY_F1                 112
#define DG_KEY_F2                 113
#define DG_KEY_F3                 114
#define DG_KEY_F4                 115
#define DG_KEY_F5                 116
#define DG_KEY_F6                 117
#define DG_KEY_F7                 118
#define DG_KEY_F8                 119
#define DG_KEY_F9                 120
#define DG_KEY_F10                121
#define DG_KEY_F11                122
#define DG_KEY_F12                123
#define DG_KEY_F13                124
#define DG_KEY_F14                125
#define DG_KEY_F15                126
#define DG_KEY_F16                127
#define DG_KEY_F17                128
#define DG_KEY_F18                129
#define DG_KEY_F19                130
#define DG_KEY_F20                131
#define DG_KEY_F21                132
#define DG_KEY_F22                133
#define DG_KEY_F23                134
#define DG_KEY_F24                135
#define DG_KEY_F25                136
#define DG_KEY_LEFT_SHIFT         16
#define DG_KEY_LEFT_CONTROL       17
#define DG_KEY_LEFT_ALT           18
#define DG_KEY_LEFT_SUPER         91
#define DG_KEY_RIGHT_SHIFT        DG_KEY_LEFT_SHIFT
#define DG_KEY_RIGHT_CONTROL      DG_KEY_LEFT_CONTROL
#define DG_KEY_RIGHT_ALT          DG_KEY_LEFT_ALT
#define DG_KEY_RIGHT_SUPER        DG_KEY_LEFT_SUPER
#define DG_KEY_MENU               93
//
#define DG_MOUSE_BUTTON_1         1
#define DG_MOUSE_BUTTON_2         2
#define DG_MOUSE_BUTTON_3         16
#define DG_MOUSE_BUTTON_4         3
#define DG_MOUSE_BUTTON_5         4
#define DG_MOUSE_BUTTON_6         5
#define DG_MOUSE_BUTTON_7         6
#define DG_MOUSE_BUTTON_8         7
#define DG_MOUSE_BUTTON_LAST      DG_MOUSE_BUTTON_8
#define DG_MOUSE_BUTTON_LEFT      DG_MOUSE_BUTTON_1
#define DG_MOUSE_BUTTON_RIGHT     DG_MOUSE_BUTTON_2
#define DG_MOUSE_BUTTON_MIDDLE    DG_MOUSE_BUTTON_3

namespace Dogo
{
	enum class KeyState
	{
		None = 0, PRESSED, REPEAT, RELEASED
	};
	enum class ButtonState
	{
		None = 0, PRESSED, REPEAT, RELEASED
	};

	class Input
	{
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int32_t keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int32_t button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static void ProcessKey(int32_t key, bool pressed) { s_Instance->ProcessKeyImpl(key, pressed); }
		inline static void ProcessButton(int32_t button, bool pressed) { s_Instance->ProcessButtonImpl(button, pressed); }
		inline static void ProcessMousePos(std::pair<int32_t, int32_t> mousepos) { s_Instance->ProcessMousePosImpl(mousepos); }
		inline static void ProcessMouseScroll(std::pair<int32_t, int32_t> scroll) { s_Instance->ProcessMouseScrollImpl(scroll); }
		inline static void ProcessMouseScrollDelta(int32_t delta) { s_Instance->ProcessScrollDeltaImpl(delta); }
	protected:
		Input() = default;
		virtual bool IsKeyPressedImpl(int32_t keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int32_t button) = 0;
		virtual void ProcessKeyImpl(int32_t key, bool pressed) = 0;
		virtual void ProcessButtonImpl(int32_t button, bool pressed) = 0;
		virtual void ProcessMousePosImpl(std::pair<int32_t, int32_t> mousepos) = 0;
		virtual void ProcessMouseScrollImpl(std::pair<int32_t, int32_t> scroll) = 0;
		virtual void ProcessScrollDeltaImpl(int32_t delta) = 0;


	public:
		inline static int32_t GetKey() { return m_Key; }
		inline static int32_t GetLastKey() { return m_LastKey; }
		inline static int32_t GetButton() { return m_Button; }
		inline static int32_t GetLastButton() { return m_LastButton; }
		inline static KeyState GetKeyState() { return m_KeyState; }
		inline static ButtonState GetButtonState() { return m_ButtonState; }
		inline static std::pair<int32_t, int32_t> GetMousePosition() { return s_Instance->m_MousePosition; }
		inline static int32_t GetMouseX() { return s_Instance->m_MousePosition.first; }
		inline static int32_t GetMouseY() { return s_Instance->m_MousePosition.second; }
		inline static std::pair<int32_t, int32_t> GetMouseScroll() { return s_Instance->m_Scroll; }
		inline static int32_t GetScrollX() { return s_Instance->m_Scroll.first; }
		inline static int32_t GetScrollY() { return s_Instance->m_Scroll.second; }
		inline static int32_t GetScrollDelta() { return s_Instance->m_ScrollDelta; }

	protected:
		inline static void SetKey(int32_t key) 
		{ 
			m_LastKey = m_Key;
			m_Key = key;
		}
		inline static void SetButton(int32_t button) 
		{ 
			m_LastButton = m_Button;
			m_Button = button;
		}
		inline static void SetKeyState(KeyState state) { m_KeyState = state; }
		inline static void SetButtonState(ButtonState state) { m_ButtonState = state; }
		inline static void SetMousePos(std::pair<int32_t, int32_t> pos)
		{
			m_MousePosition = pos;
		}
		inline static void SetScroll(std::pair<int32_t, int32_t> scroll)
		{
			m_Scroll = scroll;
		}
		inline static void SetScrollDelta(int32_t scroll)
		{
			m_ScrollDelta = scroll;
		}

	private:
		static Input* s_Instance;
		static std::pair<int32_t, int32_t> m_MousePosition;
		static std::pair<int32_t, int32_t> m_Scroll;
		static int32_t m_ScrollDelta;
		static int32_t m_Key;
		static int32_t m_Button;
		static std::pair<int32_t, int32_t> m_LastMousePosition;
		static int32_t m_LastKey;
		static int32_t m_LastButton;
		static KeyState m_KeyState;
		static ButtonState m_ButtonState;
	};


	static std::string KeyCodeToKeyName(int32_t keycode)
	{
		switch (keycode)
		{
		case DG_KEY_SPACE:
			return "Spacebar";
		case DG_KEY_APOSTROPHE:
			return "'";
		case DG_KEY_COMMA:
		{
			if (Input::GetLastKey() == DG_KEY_RIGHT_SHIFT) { Input::ProcessKey(DG_KEY_SEMICOLON, false); return ";"; }
			return ",";
		}
		case DG_KEY_MINUS:
			return "-";
		case DG_KEY_PERIOD:
		{
			if (Input::GetLastKey() == DG_KEY_RIGHT_SHIFT) { Input::ProcessKey(DG_KEY_COLON, false); return ":"; }
			return ".";
		}
		case DG_KEY_0:
		{
			if (Input::GetLastKey() == DG_KEY_RIGHT_SHIFT) { Input::ProcessKey(DG_KEY_EQUAL, false); return "="; }
			return "0";
		}
		case DG_KEY_1:
			return "1";
		case DG_KEY_2:
			return "2";
		case DG_KEY_3:
			return "3";
		case DG_KEY_4:
			return "4";
		case DG_KEY_5:
			return "5";
		case DG_KEY_6:
			return "6";
		case DG_KEY_7:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_SHIFT) { Input::ProcessKey(DG_KEY_SLASH, false); return "/"; }
			return "7";
		}
		case DG_KEY_8:
			return "8";
		case DG_KEY_9:
			return "9";
		case DG_KEY_A:
			return "A";
		case DG_KEY_B:
			return "B";
		case DG_KEY_C:
			return "C";
		case DG_KEY_D:
			return "D";
		case DG_KEY_E:
			return "E";
		case DG_KEY_F:
			return "F";
		case DG_KEY_G:
			return "G";
		case DG_KEY_H:
			return "H";
		case DG_KEY_I:
			return "I";
		case DG_KEY_J:
			return "J";
		case DG_KEY_K:
			return "K";
		case DG_KEY_L:
			return "L";
		case DG_KEY_M:
			return "M";
		case DG_KEY_N:
			return "N";
		case DG_KEY_O:
			return "O";
		case DG_KEY_P:
			return "P";
		case DG_KEY_Q:
			return "Q";
		case DG_KEY_R:
			return "R";
		case DG_KEY_S:
			return "S";
		case DG_KEY_T:
			return "T";
		case DG_KEY_U:
			return "U";
		case DG_KEY_V:
			return "V";
		case DG_KEY_W:
			return "W";
		case DG_KEY_X:
			return "X";
		case DG_KEY_Y:
			return "Y";
		case DG_KEY_Z:
			return "Z";
		case DG_KEY_GRAVE_ACCENT:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_ALT) { Input::ProcessKey(DG_KEY_LEFT_BRACKET, false); return "["; }
			return "`";
		}
		case DG_KEY_PLUS:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_ALT) { Input::ProcessKey(DG_KEY_RIGHT_BRACKET, false); return "]"; }
			return "+";
		}
		case DG_KEY_ACUTE_ACCENT:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_ALT) { Input::ProcessKey(DG_KEY_LEFT_CURLY_BRACKET, false); return "{"; }
			return "´";
		}
		case DG_KEY_CEDILHA:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_ALT) { Input::ProcessKey(DG_KEY_RIGHT_CURLY_BRACKET, false); return "}"; }
			return "ç";
		}
		case DG_KEY_DEGREE:
		{
			if (Input::GetLastKey() == DG_KEY_LEFT_ALT) { Input::ProcessKey(DG_KEY_BACKSLASH, false); return "\\"; }
			return "º";
		}
		case DG_KEY_ESCAPE:
			return "ESC";
		case DG_KEY_ENTER:
			return "ENTER";
		case DG_KEY_TAB:
			return "TAB";
		case DG_KEY_BACKSPACE:
			return "BACKSPACE";
		case DG_KEY_INSERT:
			return "INSERT";
		case DG_KEY_DELETE:
			return "DELETE";
		case DG_KEY_RIGHT:
			return "RIGHT";
		case DG_KEY_LEFT:
			return "LEFT";
		case DG_KEY_DOWN:
			return "DOWN";
		case DG_KEY_UP:
			return "UP";
		case DG_KEY_PAGE_UP:
			return "PAGE_UP";
		case DG_KEY_PAGE_DOWN:
			return "PAGE_DOWN";
		case DG_KEY_HOME:
			return "HOME";
		case DG_KEY_END:
			return "END";
		case DG_KEY_CAPS_LOCK:
			return "CAPS_LOCK";
		case DG_KEY_SCROLL_LOCK:
			return "SCROLL_LOCK";
#if AMERICAN
		case DG_KEY_NUM_LOCK:
			return "NUM_LOCK";
#endif
		case DG_KEY_PRINT_SCREEN:
			return "PRINT_SCREEN";
		case DG_KEY_PAUSE:
			return "PAUSE";
		case DG_KEY_F1:
			return "F1";
		case DG_KEY_F2:
			return "F2";
		case DG_KEY_F3:
			return "F3";
		case DG_KEY_F4:
			return "F4";
		case DG_KEY_F5:
			return "F5";
		case DG_KEY_F6:
			return "F6";
		case DG_KEY_F7:
			return "F7";
		case DG_KEY_F8:
			return "F8";
		case DG_KEY_F9:
			return "F9";
		case DG_KEY_F10:
			return "F10";
		case DG_KEY_F11:
			return "F11";
		case DG_KEY_F12:
			return "F12";
		case DG_KEY_F13:
			return "F13";
		case DG_KEY_F14:
			return "F14";
		case DG_KEY_F15:
			return "F15";
		case DG_KEY_F16:
			return "F16";
		case DG_KEY_F17:
			return "F17";
		case DG_KEY_F18:
			return "F18";
		case DG_KEY_F19:
			return "F19";
		case DG_KEY_F20:
			return "F20";
		case DG_KEY_F21:
			return "F21";
		case DG_KEY_F22:
			return "F22";
		case DG_KEY_F23:
			return "F23";
		case DG_KEY_F24:
			return "F24";
		case DG_KEY_F25:
			return "F25";
#if AMERICAN
		case DG_KEY_KP_0:
			return "KEYPAD_0";
		case DG_KEY_KP_1:
			return "KEYPAD_1";
		case DG_KEY_KP_2:
			return "KEYPAD_2";
		case DG_KEY_KP_3:
			return "KEYPAD_3";
		case DG_KEY_KP_4:
			return "KEYPAD_4";
		case DG_KEY_KP_5:
			return "KEYPAD_5";
		case DG_KEY_KP_6:
			return "KEYPAD_6";
		case DG_KEY_KP_7:
			return "KEYPAD_7";
		case DG_KEY_KP_8:
			return "KEYPAD_8";
		case DG_KEY_KP_9:
			return "KEYPAD_9";
		case DG_KEY_KP_DECIMAL:
			return "KEYPAD_DECIMAL";
		case DG_KEY_KP_MULTIPLY:
			return "KEYPAD_MULTIPLY";
		case DG_KEY_KP_DIVIDE:
			return "KEYPAD_DIVIDE";
		case DG_KEY_KP_SUBTRACT:
			return "KEYPAD_SUBTRACT";
		case DG_KEY_KP_ADD:
			return "KEYPAD_ADD";
		case DG_KEY_KP_ENTER:
			return "KEYPAD_ENTER";
		case DG_KEY_KP_EQUAL:
			return "KEYPAD_EQUAL";
#endif
		case DG_KEY_LEFT_SHIFT:
			return "SHIFT";
		case DG_KEY_LEFT_CONTROL:
			return "CONTROL";
		case DG_KEY_LEFT_ALT:
			return "ALT";
		case DG_KEY_LEFT_SUPER:
			return "SUPER";
		case DG_KEY_MENU:
			return "MENU";
		default:
		{
			DG_INFO("KeyCode: %i", keycode);
			return "Unknown key";
		}
		}
	}

	static std::string ButtonCodeToButtonName(int32_t button)
	{
		switch (button)
		{
		case DG_MOUSE_BUTTON_1:
			return "MouseButton1 / MouseButtonLeft";
		case DG_MOUSE_BUTTON_2:
			return "MouseButton2 / MouseButtonRight";
		case DG_MOUSE_BUTTON_3:
			return "MouseButton3 / MouseButtonMiddle";
		case DG_MOUSE_BUTTON_4:
			return "MouseButton4";
		case DG_MOUSE_BUTTON_5:
			return "MouseButton5";
		case DG_MOUSE_BUTTON_6:
			return "MouseButton6";
		case DG_MOUSE_BUTTON_7:
			return "MouseButton7";
		case DG_MOUSE_BUTTON_8:
			return "MouseButton8";
		default:
		{
			DG_INFO("ButtonCode: %i", button);
			return "Unknown button";
		}
		}
	}
}