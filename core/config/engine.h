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
#ifndef ENGINE_H
#define ENGINE_H


#include "core/typedefs.h"
#include <alsa/control.h>

#include <cstdlib>
#include <csignal>
#include <list>
#include <list.h>

#include <string>


struct Signleton {
    char* object;
    int* count;
    void* item;
};

class Engine {


private:
    int fps;
    int p_target;
    bool hint;
    std::list<std::string>* p_list;

    double p_time;

public:
    static Engine* GetSignleton();
public:
    int GetEngineFps(void) const;
    int GetFpsTargert(void) const;

    void SetFpsTargert(int p_fps);
    double GetFrameTime(void) const;

    bool IsEditorHint(void) const;
    bool IsHint(void) const;

    void SetPropertyList(const std::list<std::string>* p_list) const;
    std::list<std::string> GetPropertyList(void) const;


public:
    Engine();
    ~Engine();

};



#endif // ENGINE_H