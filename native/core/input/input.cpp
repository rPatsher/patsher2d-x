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

#include "input.h"

#include "core/math/vector2.h"
#include "core/math/vector3.h" 
#include "core/templates/map.h"
#include "core/templates/typed_array.h"
#include "core/string/ustring.h"
#include "core/variant/dictionary.h"


#include <SDL/SDL.h>
#include <memory>
#include <cmath>

static const char *_joy_buttons[(size_t)JoyButton::SDL_MAX] = {
	"a",
	"b",
	"x",
	"y",
	"back",
	"guide",
	"start",
	"leftstick",
	"rightstick",
	"leftshoulder",
	"rightshoulder",
	"dpup",
	"dpdown",
	"dpleft",
	"dpright",
	"misc1",
	"paddle1",
	"paddle2",
	"paddle3",
	"paddle4",
	"touchpad",
};

static const char *_joy_axes[(size_t)JoyAxis::SDL_MAX] = {
	"leftx",
	"lefty",
	"rightx",
	"righty",
	"lefttrigger",
	"righttrigger",
};


Input::Input() {
    currentKeyState = SDL_GetKeyboardState(&keyCount);
    previousKeyState = new Uint8[keyCount];
    std::memcpy(previousKeyState, currentKeyState, keyCount);

    for (int i = 0; i < keyCount; ++i) {
        keyMap[static_cast<SDL_Scancode>(i)] = false;
    }

    // Initialize mouse mode to NORMAL by default
    mouseMode = MouseMode::NORMAL;
}

Input::~Input() {
    delete[] previousKeyState;
}

float Input::get_action_strength(const String& action, bool exact) {
    if (exact) {
        return actionStrengthMap[action];
    } else {
        // Sum the strength of all keys mapped to this action
        float strength = 0.0f;
        for (const auto& pair : actionMap) {
            if (pair.second && is_key_pressed(pair.first)) {
                strength += get_action_strength(pair.first, true);
            }
        }
        return strength;
    }
}

float Input::get_axis(const String& negativeAction, const String& positiveAction) {
    float negativeStrength = get_action_strength(negativeAction, false);
    float positiveStrength = get_action_strength(positiveAction, false);

    // Return the difference between positive and negative strengths
    return positiveStrength - negativeStrength;
}

Vector2 Input::get_vector(const String& negativeX, const String& positiveX,
                           const String& negativeY, const String& positiveY,
                           float deadzone) {
    float x = get_axis(negativeX, positiveX);
    float y = get_axis(negativeY, positiveY);

    // Apply deadzone
    if (std::abs(x) < deadzone) {
        x = 0.0f;
    }

    if (std::abs(y) < deadzone) {
        y = 0.0f;
    }

    return Vector2(x, y);
}

void Input::set_mouse_mode(MouseMode mode) {
    mouseMode = mode;

    switch (mode) {
        case MouseMode::MOUSE_MODE_NORMAL:
            SDL_ShowCursor(SDL_ENABLE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
            break;

        case MouseMode::MOUSE_MODE_CAPTURED_HIDDEN:
            SDL_ShowCursor(SDL_DISABLE);
            SDL_SetRelativeMouseMode(SDL_TRUE);
            break;

        case MouseMode:: MOUSE_MODE_CAPTURED:
        	int deltaX, deltaY;
    		SDL_GetRelativeMouseState(&deltaX, &deltaY);
    		break;
        case MouseMode::MOUSE_MODE_HIDDEN:
            SDL_ShowCursor(SDL_DISABLE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
            break;
        default:
            break;
    }
}

MouseMode Input::get_mouse_mode() const {
    return mouseMode;
}

bool Input::is_key_down(SDL_Scancode key) {
    return currentKeyState[key];
}

bool Input::is_key_pressed(SDL_Scancode key) {
    return keyMap[key];
}

bool Input::is_key_released(SDL_Scancode key) {
    return (!currentKeyState[key] && previousKeyState[key]);
}

bool Input::is_key_pressed(Key keycode) {
    SDL_Scancode sdlKey = static_cast<SDL_Scancode>(keycode);
    return isKeyPressed(sdlKey);
}

bool Input::is_physical_key_pressed(Key keycode) {
    SDL_Scancode sdlKey = static_cast<SDL_Scancode>(keycode);
    return isKeyDown(sdlKey);
}

bool Input::is_action_pressed(const String& action, bool exact) {
    if (exact) {
        return actionMap[action];
    } else {
        // Check if any key mapped to this action is pressed
        for (const auto& pair : actionMap) {
            if (pair.second && is_key_pressed(pair.first)) {
                return true;
            }
        }
        return false;
    }
}

const Joypad& Input::get_joypad_state() const {
    return joypadState;
}

void Input::update() {
    // Update joypad state
    SDL_Joystick* joystick = SDL_JoystickOpen(0); // Open the first joystick
    if (joystick) {
        // Update axes
        joypadState.leftStickX = SDL_JoystickGetAxis(joystick, 0) / 32767.0f;
        joypadState.leftStickY = SDL_JoystickGetAxis(joystick, 1) / 32767.0f;
        joypadState.rightStickX = SDL_JoystickGetAxis(joystick, 2) / 32767.0f;
        joypadState.rightStickY = SDL_JoystickGetAxis(joystick, 3) / 32767.0f;

        // Update triggers
        joypadState.leftTrigger = SDL_JoystickGetAxis(joystick, 4) / 32767.0f;
        joypadState.rightTrigger = SDL_JoystickGetAxis(joystick, 5) / 32767.0f;

        // Update buttons
        joypadState.buttonA = SDL_JoystickGetButton(joystick, 0);
        joypadState.buttonB = SDL_JoystickGetButton(joystick, 1);
        joypadState.buttonX = SDL_JoystickGetButton(joystick, 2);
        joypadState.buttonY = SDL_JoystickGetButton(joystick, 3);

        // Close the joystick when done
        SDL_JoystickClose(joystick);
    }
}




void Input::set_accelerometer(const Vector3& p_accel) {
    accelerometer = p_accel;
}

void Input::set_gravity(const Vector3& p_gravity) {
    gravity = p_gravity;
}

void Input::add_joy_mapping(const String& p_mapping, bool p_update_existing) {
    // update joystick mapping
    if (p_update_existing || joystickMappings.find(p_mapping) == joystickMappings.end()) {
        joystickMappings[p_mapping] = p_mapping;
        SDL_GameControllerAddMapping(p_mapping.c_str());
    }
}

void Input::remove_joy_mapping(const String& p_guid) {
    // Remove joystick mapping based on GUID
    SDL_GameControllerMappingForGUID(SDL_JoystickGetGUIDFromString(p_guid.c_str()));
    joystickMappings.erase(p_guid);
}

bool Input::is_joy_known(int p_device) {
    // Check if a joystick with the specified device index is known
    return knownJoysticks.find(p_device) != knownJoysticks.end();
}


String Input::get_joy_guid(int p_device) {
    // Get the GUID of a joystick with the specified device index
    SDL_Joystick* joystick = SDL_JoystickOpen(p_device);
    if (joystick) {
        String guid = SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joystick));
        SDL_JoystickClose(joystick);
        return guid;
    }
    return "";
}



void Input::release_pressed_events() {
    // Release any pressed events
    SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP | SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP |
                   SDL_MOUSEMOTION | SDL_JOYBUTTONDOWN | SDL_JOYBUTTONUP | SDL_JOYAXISMOTION);
}


bool Input::should_ignore_device(int p_vendor_id, int p_product_id) {
    // Check whether to ignore a device based on vendor and product IDs
    return ignoredDevices.find(std::make_pair(p_vendor_id, p_product_id)) != ignoredDevices.end();
}


void Input::joy_button(int p_device, JoyButton p_button, bool p_pressed) {
    // Handle joystick button events
    buttonStates[std::make_pair(p_device, p_button)] = p_pressed;
}

