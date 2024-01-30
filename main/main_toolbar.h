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


#ifndef MAIN_TOOLBAR_H
#define MAIN_TOOLBAR_H

#include <core/typedefs.h>
#include <core/string/string.h>
#include <core/object/ref_counted.h>
#include <core/object/m_class.h>
#include <main/main.h>



class MainToolBar : public RefCounted {
    MCLASS(MainToolBar , RefCounted);

private:
    String name;
    Ref<MainToolBar> main;
    Ref<Rectangle> p_rect;
    Ref<Vector2> vec2;
    Ref<Vector2> p_vec;

public:
    MainToolBar* create(void) const;
    void draw(void) const; 

    Vector2 get_main_pos() const;
    Vector2 get_main_size() const;

    static void register_class() {};
    static void bind_methods();

    bool _is_class_enabled() const;
protected:
    friend class Main;

};

MCLASSDB(MainToolBar);







#endif 
