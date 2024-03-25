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
#ifndef INPUT_MAP_H
#define INPUT_MAP_H


#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class InputMap {
public:
    InputMap();
    ~InputMap();

    void add_mapping(SDL_Keycode key, const std::string& action);
    void add_action(const std::string& action, float deadzone = 0.5);
    void SetDeadzone(const std::string& action, float deadzone);
    void Erase_Events(const std::string& action);

    // Check if an action is triggered
    bool IsActionTriggered(const std::string& action);

    // Check if an action exists
    bool HasAction(const std::string& action);

    // Get a list of all actions
    std::vector<std::string> GetActions();

    // Process SDL events to update input state
    void ProcessEvents(SDL_Event& event);

private:
    std::unordered_map<SDL_Keycode, std::string> keyMappings;
    std::unordered_map<std::string, bool> actionStates;
    std::unordered_map<std::string, float> actionDeadzones;
};


#endif // INPUT_MAP_H