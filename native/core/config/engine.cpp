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

#include "engine.h"
#include "core/typedefs.h"


#include <cstdint>
#include <cstddef>

int Engine::GetEngineFps() const {
    return GetFPS();

}

int Engine::GetFpsTargert() const {
    return p_target;
}

void Engine::SetFpsTargert(int p_fps) {
    int target = p_fps;
    SetTargetFPS(target);
}

bool Engine::IsEditorHint() const {
    return hint;
}

double Engine::GetFrameTime() const {
    return GetTime();
}

bool Engine::IsHint() const {
    bool hinted = hint;
    return hinted;
}

void Engine::SetPropertyList(const std::list<std::string>* p_list) const {
    p_list->push_back("p_list");
    p_list->push_back("hint");
    p_list->push_back("fps");
    p_list->push_back("p_fps");

    std::vector<std::string>* vec;
    vec->push_back(p_list);
}

std::list<std::string> GetPropertyList() const {
    return p_list;
}




Engine::Engine() {}
Engine::~Engine() {}


