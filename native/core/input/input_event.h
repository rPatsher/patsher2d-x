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
#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include "core/templates/vector.h"
#include "core/templates/list.h"
#include "core/error/error_macros.h"
#include "core/string/ustring.h"
#include "core/object/ref_counted.h"


#include <SDL.h>
#include <cmath>
#include <unordered_map>

class Vector2;
class Vector3;
class Resource;

/**
 * @class InputEvent
 * @brief InputEvent These are used in the MainLoop
 */
 

class InputEvent : public Resource {
	CLASS(InputEvent , Resource);
public:
    static InputEvent* get_singleton();

    void process_input();

    bool is_action_pressed(const String& action, bool allowEcho = false, bool exactMatch = false) const;
    bool is_action(const String& action, bool exactMatch = false) const;
    bool is_action_released(const String& action, bool exactMatch = false) const;
    float get_action_strength(const String& action, bool exactMatch = false) const;
    float get_action_raw_strength(const String& action, bool exactMatch = false) const;
    bool is_pressed() const;
    bool is_released() const;
    bool action_match(const InputEvent& p_event, bool p_exact_match, float p_deadzone, bool* r_pressed, float* r_strength, float* r_raw_strength) const;
    bool is_match(const InputEvent& p_event, bool p_exact_match = true) const;

    void add_action_mapping(const String& action, SDL_Scancode key);
    

private:
    InputEvent();
    ~InputEvent();

    std::unordered_map<String, SDL_Scancode> m_action;
};


class InputEventScreenDrag : public InputEvent {
	CLASS(InputEventScreenDrag , InputEvent);
public:
    InputEventScreenDrag(); 
    InputEventScreenDrag(SDL_Point start, SDL_Point current);
    ~InputEventScreenDrag();

    SDL_Point get_start_position() const;
    SDL_Point get_current_position() const;
    Vector2 get_position() const;
    Vector2 get_velocity() const;
    int get_index() const;
    float get_pressure() const;
    Vector2 getTouch_point() const;
    Vector2 get_global_position() const;

    void setStartPosition(SDL_Point start);
    void setCurrentPosition(SDL_Point current);
    void setPosition(const Vector2& p_pos);
    void setTilt(const Vector2& p_tilt);
    void setIndex(int p_index);
    void setPressure(float p_pressure);
protected:
	void _bind_methods();
private:
    SDL_Point startPosition;
    SDL_Point currentPosition;
    Vector2 position; 
    Vector2 tilt;
    int index;
    float pressure;
};

class InputEventScreenTouch : public InputEvent {
	CLASS(InputEventScreenTouch , InputEvent);
public:
    InputEventScreenTouch();
    InputEventScreenTouch(SDL_TouchID touchID, SDL_Point position);
    ~InputEventScreenTouch();

    SDL_TouchID get_touch_id() const;
    SDL_Point get_position() const;
    Vector2 get_position_vector() const;
    
    Vector2 getTouchPosition() const;

    bool is_pressed() const;
    bool is_released() const;

    void set_touch_id(SDL_TouchID touchID);
    void set_position(SDL_Point position);
    void set_position(const Vector2& position);
    
    void reset_states();
    
protected:
	void _bind_methods();
private:
    SDL_TouchID touchID;
    SDL_Point position;
    bool pressed;
    bool released;
};

class InputEventMouseButton : public InputEvent {
	CLASS(InputEventMouseButton , InputEvent);
public:
	enum ButtonIndex {
    	MOUSE_LEFT = 1,
    	MOUSE_MIDDLE = 2,
    	MOUSE_RIGHT = 3
	};
public:
    InputEventMouseButton();
    InputEventMouseButton(ButtonIndex button, Uint8 state, SDL_Point position);
    ~InputEventMouseButton();

    ButtonIndex get_button() const;
    Uint8 get_state() const;
    SDL_Point get_position() const;
    Vector2 get_position_vector() const;

    void set_canceled(bool p_canceled);
    void set_pressed(bool p_pressed);

    void set_button(ButtonIndex button);
    void set_state(Uint8 state);
    void set_position(SDL_Point position);
    void set_position(const Vector2& position);
protected:
	void _bind_methods();
private:
    ButtonIndex button;
    Uint8 state;
    SDL_Point position;
    bool canceled;
    bool pressed;
};

class InputKey : public InputEvent {
public:
    InputKey();
    ~InputKey();
public:
	enum KeyCode {
    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_X,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,

    NUM_0 = SDL_SCANCODE_0,
    NUM_1 = SDL_SCANCODE_1,
    NUM_2 = SDL_SCANCODE_2,
    NUM_3 = SDL_SCANCODE_3,
    NUM_4 = SDL_SCANCODE_4,
    NUM_5 = SDL_SCANCODE_5,
    NUM_6 = SDL_SCANCODE_6,
    NUM_7 = SDL_SCANCODE_7,
    NUM_8 = SDL_SCANCODE_8,
    NUM_9 = SDL_SCANCODE_9,

    ENTER = SDL_SCANCODE_RETURN,
    ESCAPE = SDL_SCANCODE_ESCAPE,
    SPACE = SDL_SCANCODE_SPACE,

    LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
    RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,
    LEFT_CTRL = SDL_SCANCODE_LCTRL,
    RIGHT_CTRL = SDL_SCANCODE_RCTRL,
    LEFT_ALT = SDL_SCANCODE_LALT,
    RIGHT_ALT = SDL_SCANCODE_RALT
};

public:
    void handle_event(SDL_Event& event);
    bool is_key_down(KeyCode key) const;
    bool is_Key_up(KeyCode key) const;
    

private:
    std::unordered_map<SDL_Scancode, bool> keyStates;
};




#define // INPUT_EVENT_H