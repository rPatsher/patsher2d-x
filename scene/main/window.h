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

#ifndef WINDOW_H
#define WINDOW_H



#include <core/error/error_list.h>
#include <core/string/string.h>
#include <core/object/ref_counted.h>
#include <core/object/m_class.h>
#include <core/typedefs.h>
#include <scene/main/viewport.h>


#include <cstring>
#include <cstdlib>



class Window : public Viewport {
    MCLASS(Window , Viewport);


public:
    enum class Mode {
        MODE_WINDOW_BEGIN_LEFT,
        MODE_WINDOW_BEGIN_RIGHT

    };

    enum class Flags {
        FLAGS_WINDOW_FULLSCREEN = ConfigFlags::FLAG_FULLSCREEN_MODE,
        FLAGS_WINDOW_HINT = ConfigFlags::FLAG_VSYNC_HINT,
        FLAGS_WINDOW_MSAA_4X = ConfigFlags::FLAG_MSAA_4X_HINT,
        FLAGS_WINDOW_RESIZED = ConfigFlags::FLAG_WINDOW_RESIZABLE,
        FLAGS_WINDOW_MAXRESIZED = ConfigFlags::FLAG_WINDOW_MAXIMIZED,
        FLAGS_WINDOW_MINIRESIZED = ConfigFlags::FLAG_WINDOW_MINIMIZED


    };
private:
    int width;
    int height;
    bool initialize;
    bool visible;
    bool p_actived;
    char* title;

public:
    static Window* init(const int width, const int height , const char* p_title);
    Window get_init() const;

    void set_title(const char* p_title);
    char* get_title() const;

    void set_mode(Mode mode) const;
    Mode get_mode() const;

    void set_flags(Flags flags) const;
    Flags get_flags() const;

    void set_actived(bool active) const;
    bool get_actived() const;

    void set_visible(bool p_visible) const;
    bool get_visible() const;

    void show();
    void hide();


    void update() const; // update parameter of window class
    void update_pos() const; // Auto update the window pos 

    void set_size(const int p_width , const int p_height);
    Vector2 get_size() const;

    void set_position(const int x , const int y);
    Vector2 get_position() const;

    int get_dpi_width() const;
    int get_dpi_height() const;

    void set_icon(const Ref<Image> image);
    Image get_icon() const;

    int get_screen_width() const; // Get current screen width
    int get_screen_height() const;

    void is_window_closed() const;
    bool is_window_shold_closed() const;

    bool is_window_ready() const;
    bool is_window_hide() const;


    void get_scale_dpi() const;

    void set_max_size(const int width, const int height); // Set window minimum dimensions (FLAG_WINDOW_RESIZABLE)
    void set_mix_size(const int width , const int height);

    

protected:
    friend class Viewport;


public:
    Window();
    ~Window();



//BIND_ENUM(Window::Mode, MODE_WINDOW_BEGIN_LEFT);
//BIND_ENUM(Window::Mode, MODE_WINDOW_BEGIN_RIGHT);

};

#endif