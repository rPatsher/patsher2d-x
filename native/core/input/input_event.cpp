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
#include "input_event.h"

#include "core/string/ustring.h"


InputEvent::InputEvent() {}

InputEvent::~InputEvent() {}

InputEvent& InputEvent::getInstance() {
    static InputEvent instance;
    return instance;
}

void InputEvent::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Process SDL events and update input state
        // You may need to add logic for key mapping and other input types
    }
}

bool InputEvent::isActionPressed(const std::string& action, bool allowEcho, bool exactMatch) const {
    auto it = actionMappings.find(action);
    if (it == actionMappings.end()) {
        return false;
    }

    SDL_Scancode keyCode = it->second;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    if (exactMatch) {
        return keyStates[keyCode];
    } else {
        return keyStates[keyCode] || keyStates[SDL_GetScancodeFromKey(SDL_GetKeyFromScancode(keyCode))];
    }
}

bool InputEvent::isAction(const std::string& action, bool exactMatch) const {
    auto it = actionMappings.find(action);
    if (it == actionMappings.end()) {
        return false;
    }

    SDL_Scancode keyCode = it->second;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    if (exactMatch) {
        return keyStates[keyCode];
    } else {
        return keyStates[keyCode] || keyStates[SDL_GetScancodeFromKey(SDL_GetKeyFromScancode(keyCode))];
    }
}

bool InputEvent::isActionReleased(const std::string& action, bool exactMatch) const {
    auto it = actionMappings.find(action);
    if (it == actionMappings.end()) {
        return false;
    }

    SDL_Scancode keyCode = it->second;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    if (exactMatch) {
        return !keyStates[keyCode];
    } else {
        return !keyStates[keyCode] && !keyStates[SDL_GetScancodeFromKey(SDL_GetKeyFromScancode(keyCode))];
    }
}

float InputEvent::getActionStrength(const std::string& action, bool exactMatch) const {
    return isAction(action, exactMatch) ? 1.0f : 0.0f;
}

float InputEvent::get_action_rawStrength(const std::string& action, bool exactMatch) const {
    auto it = actionMappings.find(action);
    if (it == actionMappings.end()) {
        return 0.0f;
    }

    SDL_Scancode keyCode = it->second;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    return keyStates[keyCode] / 255.0f;
}

bool InputEvent::is_pressed() const {
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (keyStates[i]) {
            return true;
        }
    }
    return false;
}

bool InputEvent::is_released() const {
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (keyStates[i]) {
            return false;
        }
    }
    return true;
}

bool InputEvent::action_match(const InputEvent& p_event, bool p_exact_match, float p_deadzone, bool* r_pressed, float* r_strength, float* r_raw_strength) const {
    if (!r_pressed || !r_strength || !r_raw_strength) {
        // Check if the provided pointers are valid
        return false;
    }

    SDL_Scancode keyCode = p_event.scancode;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    *r_pressed = keyStates[keyCode];
    *r_strength = (*r_pressed) ? 1.0f : 0.0f;
    *r_raw_strength = keyStates[keyCode] / 255.0f;

    // Apply deadzone
    if (p_deadzone > 0.0f) {
        *r_strength = (*r_strength > p_deadzone) ? (*r_strength - p_deadzone) / (1.0f - p_deadzone) : 0.0f;
        *r_raw_strength = (*r_raw_strength > p_deadzone) ? (*r_raw_strength - p_deadzone) / (1.0f - p_deadzone) : 0.0f;
    }

    // check for exact match
    if (p_exact_match) {
        *r_pressed = (*r_strength > 0.0f);
        *r_raw_strength = (*r_strength > 0.0f) ? 1.0f : 0.0f;
    }

    return true;
}

bool InputEvent::isMatch(const InputEvent& p_event, bool p_exact_match) const {
    SDL_Scancode keyCode = p_event.scancode;
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    return (p_exact_match) ? keyStates[keyCode] : (keyStates[keyCode] || keyStates[SDL_GetScancodeFromKey(SDL_GetKeyFromScancode(keyCode))]);
}

void InputEvent::add_action_mapping(const String& action, SDL_Scancode key) {
    actionMappings[action] = key;
}

InputEventScreenDrag::InputEventScreenDrag(SDL_Point start, SDL_Point current)
    : startPosition(start), currentPosition(current), index(-1), pressure(1.0f) {}

InputEventScreenDrag::~InputEventScreenDrag() {}

SDL_Point InputEventScreenDrag::getStartPosition() const {
    return startPosition;
}

SDL_Point InputEventScreenDrag::getCurrentPosition() const {
    return currentPosition;
}

Vector2 InputEventScreenDrag::getPosition() const {
    return position;
}

Vector2 InputEventScreenDrag::getVelocity() const {
    // Assuming you have a method to calculate velocity based on start and current positions
    // Adjust this logic according to your requirements
    float deltaTime = 0.0167f; // Example deltaTime, adjust as needed
    Vector2 velocity = (position - Vector2(startPosition)) / deltaTime;
    return velocity;
}

int InputEventScreenDrag::getIndex() const {
    return index;
}

float InputEventScreenDrag::getPressure() const {
    return pressure;
}

Vector2 InputEventScreenDrag::getTouchPoint() const {
    return Vector2(currentPosition.x - startPosition.x, currentPosition.y - startPosition.y);
}

Vector2 InputEventScreenDrag::getGlobalPosition() const {
    return Vector2(currentPosition.x, currentPosition.y);
}

void InputEventScreenDrag::setStartPosition(SDL_Point start) {
    startPosition = start;
}

void InputEventScreenDrag::setCurrentPosition(SDL_Point current) {
    currentPosition = current;
}

void InputEventScreenDrag::setPosition(const Vector2& p_pos) {
    position = p_pos;
}

void InputEventScreenDrag::setTilt(const Vector2& p_tilt) {
    tilt = p_tilt;
}

void InputEventScreenDrag::setIndex(int p_index) {
    index = p_index;
}

void InputEventScreenDrag::setPressure(float p_pressure) {
    pressure = p_pressure;
}

InputEventScreenTouch::InputEventScreenTouch()
    : touchID(-1), position({0, 0}), pressed(false), released(false) {}

InputEventScreenTouch::InputEventScreenTouch(SDL_TouchID touchID, SDL_Point position)
    : touchID(touchID), position(position), pressed(false), released(false) {}

InputEventScreenTouch::~InputEventScreenTouch() {}

SDL_TouchID InputEventScreenTouch::getTouchID() const {
    return touchID;
}

SDL_Point InputEventScreenTouch::getPosition() const {
    return position;
}

Vector2 InputEventScreenTouch::getPositionVector() const {
    return Vector2(position.x, position.y);
}

Vector2 InputEventScreenTouch::getTouchPosition() const {
    return getPositionVector(); // Assuming you want the touch position as a Vector2
}

bool InputEventScreenTouch::isPressed() const {
    return pressed;
}

bool InputEventScreenTouch::isReleased() const {
    return released;
}

void InputEventScreenTouch::setTouchID(SDL_TouchID touchID) {
    this->touchID = touchID;
}

void InputEventScreenTouch::setPosition(SDL_Point position) {
    this->position = position;
}

void InputEventScreenTouch::setPosition(const Vector2& position) {
    this->position.x = static_cast<int>(position.x);
    this->position.y = static_cast<int>(position.y);
}

// Add the following member function to reset pressed and released states
void InputEventScreenTouch::reset_states() {
    pressed = false;
    released = false;
}


InputEventMouseButton::InputEventMouseButton()
    : button(MOUSE_LEFT), state(0), position({0, 0}), canceled(false), pressed(false) {}

InputEventMouseButton::InputEventMouseButton(ButtonIndex button, Uint8 state, SDL_Point position)
    : button(button), state(state), position(position), canceled(false), pressed(false) {}

InputEventMouseButton::~InputEventMouseButton() {}

ButtonIndex InputEventMouseButton::getButton() const {
    return button;
}

Uint8 InputEventMouseButton::getState() const {
    return state;
}

SDL_Point InputEventMouseButton::getPosition() const {
    return position;
}

Vector2 InputEventMouseButton::getPositionVector() const {
    return Vector2(position.x, position.y);
}

void InputEventMouseButton::setButton(ButtonIndex button) {
    this->button = button;
}

void InputEventMouseButton::setState(Uint8 state) {
    this->state = state;
}

void InputEventMouseButton::setPosition(SDL_Point position) {
    this->position = position;
}

void InputEventMouseButton::setPosition(const Vector2& position) {
    this->position.x = static_cast<int>(position.x);
    this->position.y = static_cast<int>(position.y);
}

// New function implementations
void InputEventMouseButton::setCanceled(bool p_canceled) {
    canceled = p_canceled;
}

void InputEventMouseButton::setPressed(bool p_pressed) {
    pressed = p_pressed;
}


InputEventMouseMotion::InputEventMouseMotion()
    : x(0), y(0), xrel(0), yrel(0) {}

InputEventMouseMotion::InputEventMouseMotion(int x, int y, int xrel, int yrel)
    : x(x), y(y), xrel(xrel), yrel(yrel) {}

InputEventMouseMotion::~InputEventMouseMotion() {}

int InputEventMouseMotion::getX() const {
    return x;
}

int InputEventMouseMotion::getY() const {
    return y;
}

int InputEventMouseMotion::getRelativeX() const {
    return xrel;
}

int InputEventMouseMotion::getRelativeY() const {
    return yrel;
}

// New function implementation
Vector2 InputEventMouseMotion::getScreenVelocity() const {
    return Vector2(xrel, yrel);
}

void InputEventMouseMotion::setScreenVelocity(const Vector2& velocity) {
    xrel = static_cast<int>(velocity.x);
    yrel = static_cast<int>(velocity.y);
}

void InputEventMouseMotion::setX(int x) {
    this->x = x;
}

void InputEventMouseMotion::setY(int y) {
    this->y = y;
}

void InputEventMouseMotion::setRelativeX(int xrel) {
    this->xrel = xrel;
}

void InputEventMouseMotion::setRelativeY(int yrel) {
    this->yrel = yrel;
}

InputKey::InputKey() {
    // Initialize key states
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        keyStates[static_cast<SDL_Scancode>(i)] = false;
    }
}

InputKey::~InputKey() {
    // Destructor
}

void InputKey::handle_event(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        keyStates[event.key.keysym.scancode] = true;
    } else if (event.type == SDL_KEYUP) {
        keyStates[event.key.keysym.scancode] = false;
    }
}

bool InputKey::is_key_down(KeyCode key) const {
    auto it = keyStates.find(static_cast<SDL_Scancode>(key));
    return (it != keyStates.end()) ? it->second : false;
}

bool InputKey::is_key_up(KeyCode key) const {
    return !isKeyDown(key);
}



