/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef INPUT_H
#define INPUT_H

#include "core/object/m_object.h"
#include "core/object/m_class.h"
#include "core/templates/vector.h" 
#include "core/templates/hash_map.h" 
#include "core/templates/hash_set.h" 
#include "core/input/default_map.h"

#include <SDL.h> // include SDL for manage input and joypad and joybutton


class Vector2;
class Vector3;
class String;

template<typename T>
class Dictionary;


class Input : public Object {
	CLASS(Input , Object);

	static Input *singleton;

	static constexpr uint64_t MAX_EVENT = 32;
	
public:
	enum Key {
    	KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    	KEY_APOSTROPHE      = 39,       // Key: '
    	KEY_COMMA           = 44,       // Key: ,
    	KEY_MINUS           = 45,       // Key: -
    	KEY_PERIOD          = 46,       // Key: .
    	KEY_SLASH           = 47,       // Key: /
    	KEY_ZERO            = 48,       // Key: 0
    	KEY_ONE             = 49,       // Key: 1
    	KEY_TWO             = 50,       // Key: 2
    	KEY_THREE           = 51,       // Key: 3
    	KEY_FOUR            = 52,       // Key: 4
    	KEY_FIVE            = 53,       // Key: 5
    	KEY_SIX             = 54,       // Key: 6
    	KEY_SEVEN           = 55,       // Key: 7
    	KEY_EIGHT           = 56,       // Key: 8
    	KEY_NINE            = 57,       // Key: 9
    	KEY_SEMICOLON       = 59,       // Key: ;
    	KEY_EQUAL           = 61,       // Key: =
    	KEY_A               = 65,       // Key: A | a
    	KEY_B               = 66,       // Key: B | b
    	KEY_C               = 67,       // Key: C | c
    	KEY_D               = 68,       // Key: D | d
    	KEY_E               = 69,       // Key: E | e
    	KEY_F               = 70,       // Key: F | f
    	KEY_G               = 71,       // Key: G | g
    	KEY_H               = 72,       // Key: H | h
    	KEY_I               = 73,       // Key: I | i
    	KEY_J               = 74,       // Key: J | j
    	KEY_K               = 75,       // Key: K | k
    	KEY_L               = 76,       // Key: L | l
    	KEY_M               = 77,       // Key: M | m
    	KEY_N               = 78,       // Key: N | n
    	KEY_O               = 79,       // Key: O | o
    	KEY_P               = 80,       // Key: P | p
    	KEY_Q               = 81,       // Key: Q | q
    	KEY_R               = 82,       // Key: R | r
    	KEY_S               = 83,       // Key: S | s
    	KEY_T               = 84,       // Key: T | t
    	KEY_U               = 85,       // Key: U | u
    	KEY_V               = 86,       // Key: V | v
    	KEY_W               = 87,       // Key: W | w
    	KEY_X               = 88,       // Key: X | x
    	KEY_Y               = 89,       // Key: Y | y
    	KEY_Z               = 90,       // Key: Z | z
    	KEY_LEFT_BRACKET    = 91,       // Key: [
    	KEY_BACKSLASH       = 92,       // Key: '\'
    	KEY_RIGHT_BRACKET   = 93,       // Key: ]
    	KEY_GRAVE           = 96,       // Key: `
    // Function keys
    	KEY_SPACE           = 32,       // Key: Space
    	KEY_ESCAPE          = 256,      // Key: Esc
    	KEY_ENTER           = 257,      // Key: Enter
    	KEY_TAB             = 258,      // Key: Tab
    	KEY_BACKSPACE       = 259,      // Key: Backspace
    	KEY_INSERT          = 260,      // Key: Ins
    	KEY_DELETE          = 261,      // Key: Del
    	KEY_RIGHT           = 262,      // Key: Cursor right
    	KEY_LEFT            = 263,      // Key: Cursor left
    	KEY_DOWN            = 264,      // Key: Cursor down
    	KEY_UP              = 265,      // Key: Cursor up
    	KEY_PAGE_UP         = 266,      // Key: Page up
    	KEY_PAGE_DOWN       = 267,      // Key: Page down
    	KEY_HOME            = 268,      // Key: Home
    	KEY_END             = 269,      // Key: End
    	KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    	KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    	KEY_NUM_LOCK        = 282,      // Key: Num lock
    	KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    	KEY_PAUSE           = 284,      // Key: Pause
    	KEY_F1              = 290,      // Key: F1
    	KEY_F2              = 291,      // Key: F2
    	KEY_F3              = 292,      // Key: F3
    	KEY_F4              = 293,      // Key: F4
    	KEY_F5              = 294,      // Key: F5
    	KEY_F6              = 295,      // Key: F6
    	KEY_F7              = 296,      // Key: F7
    	KEY_F8              = 297,      // Key: F8
    	KEY_F9              = 298,      // Key: F9
    	KEY_F10             = 299,      // Key: F10
    	KEY_F11             = 300,      // Key: F11
    	KEY_F12             = 301,      // Key: F12
    	KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    	KEY_LEFT_CONTROL    = 341,      // Key: Control left
    	KEY_LEFT_ALT        = 342,      // Key: Alt left
    	KEY_LEFT_SUPER      = 343,      // Key: Super left
    	KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    	KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    	KEY_RIGHT_ALT       = 346,      // Key: Alt right
    	KEY_RIGHT_SUPER     = 347,      // Key: Super right
    	KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    	KEY_KP_0            = 320,      // Key: Keypad 0
    	KEY_KP_1            = 321,      // Key: Keypad 1
    	KEY_KP_2            = 322,      // Key: Keypad 2
   		KEY_KP_3            = 323,      // Key: Keypad 3
    	KEY_KP_4            = 324,      // Key: Keypad 4
    	KEY_KP_5            = 325,      // Key: Keypad 5
    	KEY_KP_6            = 326,      // Key: Keypad 6
    	KEY_KP_7            = 327,      // Key: Keypad 7
    	KEY_KP_8            = 328,      // Key: Keypad 8
    	KEY_KP_9            = 329,      // Key: Keypad 9
    	KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    	KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    	KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    	KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    	KEY_KP_ADD          = 334,      // Key: Keypad +
    	KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    	KEY_KP_EQUAL        = 336,      // Key: Keypad =
    // Android key buttons
    	KEY_BACK            = 4,        // Key: Android back button
    	KEY_MENU            = 82,       // Key: Android menu button
    	KEY_VOLUME_UP       = 24,       // Key: Android volume up button
    	KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
	};
	enum MouseMode {
		MOUSE_MODE_NORMAL
		MOUSE_MODE_VISIBLE,
		MOUSE_MODE_HIDDEN,
		MOUSE_MODE_CAPTURED,
		MOUSE_MODE_CONFINED,
		MOUSE_MODE_CONFINED_HIDDEN,
	};
	enum JoyButton {
    	JOY_BUTTON_A,
    	JOY_BUTTON_B,
    	JOY_BUTTON_X,
    	JOY_BUTTON_Y,
    	JOY_BUTTON_COUNT
	};

	struct ActionState {
		uint64_t pressed_physics_frame = UINT64_MAX;
		uint64_t pressed_process_frame = UINT64_MAX;
		uint64_t released_physics_frame = UINT64_MAX;
		uint64_t released_process_frame = UINT64_MAX;
		bool exact = true;
	};
	struct DeviceState {
		bool pressed[MAX_EVENT] = { false };
		float strength[MAX_EVENT] = { 0.0 };
		float raw_strength[MAX_EVENT] = { 0.0 };
	};
		bool api_pressed = false;
		float api_strength = 0.0;
		HashMap<int, DeviceState> device_states;
		HashMap<String, ActionState> action_states;

	bool emulate_touch_from_mouse = false;
	bool emulate_mouse_from_touch = false;
	bool use_input_buffering = false;
	bool use_accumulated_input = true;

	int mouse_from_touch_index = -1;

	HashMap<int, VibrationInfo> joy_vibration;
	struct Joypad {
		String name;
		String uid;
		bool connected = false;
		bool last_buttons[(size_t)JoyButton::MAX] = { false };
		float last_axis[(size_t)JoyAxis::MAX] = { 0.0f };
		HatMask last_hat = HatMask::CENTER;
		int mapping = -1;
		int hat_current = 0;
		Dictionary<String> info;
	};

	VelocityTrack mouse_velocity_track;
	HashMap<int, VelocityTrack> touch_velocity_track;
	HashMap<int, Joypad> joy_names;

	HashSet<uint32_t> ignored_device_ids;

	int fallback_mapping = -1;
	
	
protected:
	static void _bind_methods();

public:
	void set_mouse_mode(MouseMode p_mode);
	MouseMode get_mouse_mode() const;
	void get_argument_options(const String &p_function, int p_idx, List<String> *r_options) const override;

	static Input *get_singleton();

	bool is_anything_pressed() const;
	bool is_key_pressed(Key p_keycode) const;
	bool is_physical_key_pressed(Key p_keycode) const;
	bool is_key_label_pressed(Key p_keycode) const;
	bool is_mouse_button_pressed(MouseButton p_button) const;
	bool is_joy_button_pressed(int p_device, JoyButton p_button) const;
	bool is_action_pressed(const String &p_action, bool p_exact = false) const;
	bool is_action_just_pressed(const String &p_action, bool p_exact = false) const;
	bool is_action_just_released(const String &p_action, bool p_exact = false) const;
	float get_action_strength(const String &p_action, bool p_exact = false) const;
	float get_action_raw_strength(const String &p_action, bool p_exact = false) const;
	
	void update();
	bool is_key_down(SDL_Scancode key);
    bool is_key_pressed(SDL_Scancode key);
    bool is_key_released(SDL_Scancode key);

    bool is_key_pressed(Key keycode);
    bool is_physical_key_pressed(Key keycode);
    
    float get_axis(const String& negativeAction, const String& positiveAction);
    Vector2 get_vector(const String& negativeX, const String& positiveX,
                       const String& negativeY, const String& positiveY,
                       float deadzone);

    void set_mouse_mode(MouseMode mode);
    MouseMode get_mouse_mode() const;
	
private:
	Joypad joypadState;
    Vector3 accelerometer;
    Vector3 gravity;

    // NOTE:  New members to store joystick mappings, known joysticks, ignored devices, button states, accumulated input flag, mouse position, and button mask
    std::unordered_map<String, String> joystickMappings;
    std::unordered_map<int, bool> knownJoysticks;
    std::unordered_map<std::pair<int, int>, bool> ignoredDevices;
    std::unordered_map<std::pair<int, JoyButton>, bool> buttonStates;
    bool useAccumulatedInput;
    Vector3 mousePosition;
    Uint32 mouseButtonMask;
    
    Vector3 gravity;
	Vector3 accelerometer;
	Vector3 magnetometer;
	Vector3 gyroscope;
	Vector2 mouse_pos;
	int64_t mouse_window = 0;
	bool legacy_just_pressed_behavior = false;
};



#endif // INPUT_H