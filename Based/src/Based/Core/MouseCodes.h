#pragma once

namespace Based {
typedef enum class MouseCode : uint16_t {
  // From glmfw3.h
  Button0                = 0,
	Button1                = 1,
	Button2                = 2,
	Button3                = 3,
	Button4                = 4,
	Button5                = 5,
	Button6                = 6,
	Button7                = 7,

	ButtonLast             = Button7,
	ButtonLeft             = Button0,
	ButtonRight            = Button1,
	ButtonMiddle           = Button2
} Mouse;

  inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode) {
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

// From glfw3.h
#define BSD_MOUSE_BUTTON_0      ::Based::Mouse::Button0
#define BSD_MOUSE_BUTTON_1      ::Based::Mouse::Button1
#define BSD_MOUSE_BUTTON_2      ::Based::Mouse::Button2
#define BSD_MOUSE_BUTTON_3      ::Based::Mouse::Button3
#define BSD_MOUSE_BUTTON_4      ::Based::Mouse::Button4
#define BSD_MOUSE_BUTTON_5      ::Based::Mouse::Button5
#define BSD_MOUSE_BUTTON_6      ::Based::Mouse::Button6
#define BSD_MOUSE_BUTTON_7      ::Based::Mouse::Button7
#define BSD_MOUSE_BUTTON_LAST   ::Based::Mouse::ButtonLast
#define BSD_MOUSE_BUTTON_LEFT   ::Based::Mouse::ButtonLeft
#define BSD_MOUSE_BUTTON_RIGHT  ::Based::Mouse::ButtonRight
#define BSD_MOUSE_BUTTON_MIDDLE ::Based::Mouse::ButtonMiddle
