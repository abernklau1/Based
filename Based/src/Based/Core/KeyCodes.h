#pragma once


namespace Based {
typedef enum class KeyCode : uint16_t {
// From glfw3.h

Space = 32,
Apostrophe = 39, /* ' */
Comma = 44,      /* , */
Minus = 45,      /* - */
Period = 46,     /* . */
Slash = 47,      /* / */

D0 = 48,
D1 = 49,
D2 = 50,
D3 = 51,
D4 = 52,
D5 = 53,
D6 = 54,
D7 = 55,
D8 = 56,
D9 = 57,

Semicolon = 59, /* ; */
Equal = 61,     /* = */

A = 65,
B = 66,
C = 67,
D = 68,
E = 69,
F = 70,
G = 71,
H = 72,
I = 73,
J = 74,
K = 75,
L = 76,
M = 77,
N = 78,
O = 79,
P = 80,
Q = 81,
R = 82,
S = 83,
T = 84,
U = 85,
V = 86,
W = 87,
X = 88,
Y = 89,
Z = 90,

LeftBracket = 91,  /* [ */
Backslash = 92,     /* \ */
RightBracket = 93, /* ] */
GraveAccent = 96,  /* ` */

World1 = 161,      /* non-US #1 */
World2 = 162,      /* non-US #2 */

/* Function keys */
Escape = 256,
Enter = 257,
Tab = 258,
Backspace = 259,
Insert = 260,
Delete = 261,
Right = 262,
Left = 263,
Down = 264,
Up = 265,
PageUp = 266,
PageDown = 267,
Home = 268,
End = 269,
CapsLock = 280,
ScrollLock = 281,
NumLock = 282,
PrintScreen = 283,
Pause = 284,
F1 = 290,
F2 = 291,
F3 = 292,
F4 = 293,
F5 = 294,
F6 = 295,
F7 = 296,
F8 = 297,
F9 = 298,
F10 = 299,
F11 = 300,
F12 = 301,
F13 = 302,
F14 = 303,
F15 = 304,
F16 = 305,
F17 = 306,
F18 = 307,
F19 = 308,
F20 = 309,
F21 = 310,
F22 = 311,
F23 = 312,
F24 = 313,
F25 = 314,

// Keypad
KP0 = 320,
KP1 = 321,
KP2 = 322,
KP3 = 323,
KP4 = 324,
KP5 = 325,
KP6 = 326,
KP7 = 327,
KP8 = 328,
KP9 = 329,
KPDecimal = 330,
KPDivide = 331,
KPMultiply = 332,
KPSubtract = 333,
KPAdd = 334,
KPEnter = 335,
KPEqual = 336,

LeftShift = 340,
LeftControl = 341,
LeftAlt = 342,
LeftSuper = 343,
RightShift = 344,
RightControl = 345,
RightAlt = 346,
RightSuper = 347,
Menu = 348,
} Key;
inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode) {
  os << static_cast<int32_t>(keyCode);
  return os;
}
}

// From glfw3.h
#define BSD_KEY_SPACE           ::Based::Key::Space
#define BSD_KEY_APOSTROPHE      ::Based::Key::Apostrophe    /* ' */
#define BSD_KEY_COMMA           ::Based::Key::Comma         /* , */
#define BSD_KEY_MINUS           ::Based::Key::Minus         /* - */
#define BSD_KEY_PERIOD          ::Based::Key::Period        /* . */
#define BSD_KEY_SLASH           ::Based::Key::Slash         /* / */
#define BSD_KEY_0               ::Based::Key::D0
#define BSD_KEY_1               ::Based::Key::D1
#define BSD_KEY_2               ::Based::Key::D2
#define BSD_KEY_3               ::Based::Key::D3
#define BSD_KEY_4               ::Based::Key::D4
#define BSD_KEY_5               ::Based::Key::D5
#define BSD_KEY_6               ::Based::Key::D6
#define BSD_KEY_7               ::Based::Key::D7
#define BSD_KEY_8               ::Based::Key::D8
#define BSD_KEY_9               ::Based::Key::D9
#define BSD_KEY_SEMICOLON       ::Based::Key::Semicolon     /* ; */
#define BSD_KEY_EQUAL           ::Based::Key::Equal         /* = */
#define BSD_KEY_A               ::Based::Key::A
#define BSD_KEY_B               ::Based::Key::B
#define BSD_KEY_C               ::Based::Key::C
#define BSD_KEY_D               ::Based::Key::D
#define BSD_KEY_E               ::Based::Key::E
#define BSD_KEY_F               ::Based::Key::F
#define BSD_KEY_G               ::Based::Key::G
#define BSD_KEY_H               ::Based::Key::H
#define BSD_KEY_I               ::Based::Key::I
#define BSD_KEY_J               ::Based::Key::J
#define BSD_KEY_K               ::Based::Key::K
#define BSD_KEY_L               ::Based::Key::L
#define BSD_KEY_M               ::Based::Key::M
#define BSD_KEY_N               ::Based::Key::N
#define BSD_KEY_O               ::Based::Key::O
#define BSD_KEY_P               ::Based::Key::P
#define BSD_KEY_Q               ::Based::Key::Q
#define BSD_KEY_R               ::Based::Key::R
#define BSD_KEY_S               ::Based::Key::S
#define BSD_KEY_T               ::Based::Key::T
#define BSD_KEY_U               ::Based::Key::U
#define BSD_KEY_V               ::Based::Key::V
#define BSD_KEY_W               ::Based::Key::W
#define BSD_KEY_X               ::Based::Key::X
#define BSD_KEY_Y               ::Based::Key::Y
#define BSD_KEY_Z               ::Based::Key::Z
#define BSD_KEY_LEFT_BRACKET    ::Based::Key::LeftBracket   /* [ */
#define BSD_KEY_BACKSLASH       ::Based::Key::Backslash     /* \ */
#define BSD_KEY_RIGHT_BRACKET   ::Based::Key::RightBracket  /* ] */
#define BSD_KEY_GRAVE_ACCENT    ::Based::Key::GraveAccent   /* ` */
#define BSD_KEY_WORLD_1         ::Based::Key::World1        /* non-US #1 */
#define BSD_KEY_WORLD_2         ::Based::Key::World2        /* non-US #2 */

/* Function keys */
#define BSD_KEY_ESCAPE          ::Based::Key::Escape
#define BSD_KEY_ENTER           ::Based::Key::Enter
#define BSD_KEY_TAB             ::Based::Key::Tab
#define BSD_KEY_BACKSPACE       ::Based::Key::Backspace
#define BSD_KEY_INSERT          ::Based::Key::Insert
#define BSD_KEY_DELETE          ::Based::Key::Delete
#define BSD_KEY_RIGHT           ::Based::Key::Right
#define BSD_KEY_LEFT            ::Based::Key::Left
#define BSD_KEY_DOWN            ::Based::Key::Down
#define BSD_KEY_UP              ::Based::Key::Up
#define BSD_KEY_PAGE_UP         ::Based::Key::PageUp
#define BSD_KEY_PAGE_DOWN       ::Based::Key::PageDown
#define BSD_KEY_HOME            ::Based::Key::Home
#define BSD_KEY_END             ::Based::Key::End
#define BSD_KEY_CAPS_LOCK       ::Based::Key::CapsLock
#define BSD_KEY_SCROLL_LOCK     ::Based::Key::ScrollLock
#define BSD_KEY_NUM_LOCK        ::Based::Key::NumLock
#define BSD_KEY_PRINT_SCREEN    ::Based::Key::PrintScreen
#define BSD_KEY_PAUSE           ::Based::Key::Pause
#define BSD_KEY_F1              ::Based::Key::F1
#define BSD_KEY_F2              ::Based::Key::F2
#define BSD_KEY_F3              ::Based::Key::F3
#define BSD_KEY_F4              ::Based::Key::F4
#define BSD_KEY_F5              ::Based::Key::F5
#define BSD_KEY_F6              ::Based::Key::F6
#define BSD_KEY_F7              ::Based::Key::F7
#define BSD_KEY_F8              ::Based::Key::F8
#define BSD_KEY_F9              ::Based::Key::F9
#define BSD_KEY_F10             ::Based::Key::F10
#define BSD_KEY_F11             ::Based::Key::F11
#define BSD_KEY_F12             ::Based::Key::F12
#define BSD_KEY_F13             ::Based::Key::F13
#define BSD_KEY_F14             ::Based::Key::F14
#define BSD_KEY_F15             ::Based::Key::F15
#define BSD_KEY_F16             ::Based::Key::F16
#define BSD_KEY_F17             ::Based::Key::F17
#define BSD_KEY_F18             ::Based::Key::F18
#define BSD_KEY_F19             ::Based::Key::F19
#define BSD_KEY_F20             ::Based::Key::F20
#define BSD_KEY_F21             ::Based::Key::F21
#define BSD_KEY_F22             ::Based::Key::F22
#define BSD_KEY_F23             ::Based::Key::F23
#define BSD_KEY_F24             ::Based::Key::F24
#define BSD_KEY_F25             ::Based::Key::F25

/* Keypad */
#define BSD_KEY_KP_0            ::Based::Key::KP0
#define BSD_KEY_KP_1            ::Based::Key::KP1
#define BSD_KEY_KP_2            ::Based::Key::KP2
#define BSD_KEY_KP_3            ::Based::Key::KP3
#define BSD_KEY_KP_4            ::Based::Key::KP4
#define BSD_KEY_KP_5            ::Based::Key::KP5
#define BSD_KEY_KP_6            ::Based::Key::KP6
#define BSD_KEY_KP_7            ::Based::Key::KP7
#define BSD_KEY_KP_8            ::Based::Key::KP8
#define BSD_KEY_KP_9            ::Based::Key::KP9
#define BSD_KEY_KP_DECIMAL      ::Based::Key::KPDecimal
#define BSD_KEY_KP_DIVIDE       ::Based::Key::KPDivide
#define BSD_KEY_KP_MULTIPLY     ::Based::Key::KPMultiply
#define BSD_KEY_KP_SUBTRACT     ::Based::Key::KPSubtract
#define BSD_KEY_KP_ADD          ::Based::Key::KPAdd
#define BSD_KEY_KP_ENTER        ::Based::Key::KPEnter
#define BSD_KEY_KP_EQUAL        ::Based::Key::KPEqual

#define BSD_KEY_LEFT_SHIFT      ::Based::Key::LeftShift
#define BSD_KEY_LEFT_CONTROL    ::Based::Key::LeftControl
#define BSD_KEY_LEFT_ALT        ::Based::Key::LeftAlt
#define BSD_KEY_LEFT_SUPER      ::Based::Key::LeftSuper
#define BSD_KEY_RIGHT_SHIFT     ::Based::Key::RightShift
#define BSD_KEY_RIGHT_CONTROL   ::Based::Key::RightControl
#define BSD_KEY_RIGHT_ALT       ::Based::Key::RightAlt
#define BSD_KEY_RIGHT_SUPER     ::Based::Key::RightSuper
#define BSD_KEY_MENU            ::Based::Key::Menu
