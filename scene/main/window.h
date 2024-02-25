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



#include "core/string/ustring.h"
#include "core/templates/pair.h"
#include "core/templates/vector.h"
#include "core/templates/list.h"

class Node;
class Object;
class RefCounted;
class Class;
class Vector2;

#include <cstring>
#include <cstdlib>
#include <pair>

#include <SDL.h>

class Window : public Node {
    CLASS(Window , Node);


public:
    enum Mode {
        MODE_WINDOW_BEGIN_LEFT,
        MODE_WINDOW_BEGIN_RIGHT,
        MODE_WINDOW_MODE_WINDOWED,
    	MODE_WINDOW_MODE_FULLSCREEN_DESKTOP,
    	MODE_WINDOW_MODE_BORDERLESS
    };

    enum Flags {
        FLAGS_WINDOW_FULLSCREEN = ConfigFlags::FLAG_FULLSCREEN_MODE,
        FLAGS_WINDOW_HINT = ConfigFlags::FLAG_VSYNC_HINT,
        FLAGS_WINDOW_MSAA_4X = ConfigFlags::FLAG_MSAA_4X_HINT,
        FLAGS_WINDOW_RESIZED = ConfigFlags::FLAG_WINDOW_RESIZABLE,
        FLAGS_WINDOW_MAXRESIZED = ConfigFlags::FLAG_WINDOW_MAXIMIZED,
        FLAGS_WINDOW_MINIRESIZED = ConfigFlags::FLAG_WINDOW_MINIMIZED,
        FLAGS_WINDOW_FLAG_POPUP = SDL_WINDOW_POPUP
    };
public:
	struct Matrix4 {
		float elements[4][4];
	};
	
	Matrix4 get_screen_transform_internal(bool p_absolute_position) const;
	
public:
    void init(const int width, const int height , const char* p_title);
    Window get_init() const;
    void close();
    bool is_init() const;
    void reset_size();
    void move_to_center();
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
	void popup(const Vector2& p_screen_rect);
    void popup_centered_ratio(float p_ratio);
    void update() const; 
    void update_pos() const; 
    void set_size(const int p_width , const int p_height);
    Vector2 get_size() const;
    void set_position(const int x , const int y);
    Vector2 get_position() const;
    int get_dpi_width() const;
    int get_dpi_height() const;
    void set_icon(const Ref<Image> image);
    Image get_icon() const;
    int get_screen_width() const; 
    int get_screen_height() const;
    void is_window_closed() const;
    bool is_window_shold_closed() const;
    bool is_window_ready() const;
    bool is_window_hide() const;
	std::pair<int, int> get_size() const;
    std::pair<int, int> get_size_with_decorations() const;
    std::pair<int, int> get_position() const;
    void get_scale_dpi() const;
    void set_max_size(const int width, const int height); 
    void set_mix_size(const int width , const int height);
	int get_current_screen() const;
    void set_current_screen(int screenIndex);
    
    

protected:
    friend class Viewport;
    friend class Node;
    void _bind_methods() {}

private:
	SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Mode p_mode;
    int currentScreen;
    int originalWidth;
    int originalHeight;
    bool visible;
    bool active;
    char* title;
public:
    Window();
    ~Window();

};

#endif // WINDOW_H