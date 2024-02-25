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
#include "window.h"



#include "core/error/error_list.h"
#include "core/error/error_macros.h"
#include "core/object/m_object.h"
#include "core/object/m_class.h"
#include "core/object/ref_counted.h"
#include "scene/main/node.h"
#include "scene/property_utils.h"
#include "core/typedefs.h"

#include <pair>
#include <cstdio>
#include <cmath>


#if defined(_WIN32) || defined(__linux__)
    #define PLATFORM_SDL_DESKTOP
#elif defined(__ANDROID__) || defined(__EMSCRIPTEN__)
    #define PLATFORM_SDL_MOBILE
#endif



Window::Window() :
    window(nullptr),
    renderer(nullptr),
    running(false),
    windowMode(WINDOW_MODE_WINDOWED),
    currentScreen(0),
    originalWidth(800),
    originalHeight(600),
    visible(true) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle initialization error
        // You can add error handling code here
    }

    Uint32 flags = 0;

    switch (windowMode) {
        case FLAGS_WINDOW_MODE_WINDOWED:
            flags = SDL_WINDOW_SHOWN;
            break;
        case FLAGS_WINDOW_MODE_FULLSCREEN:
            flags = SDL_WINDOW_FULLSCREEN;
            break;
        case FLAGS_WINDOW_MODE_FULLSCREEN_DESKTOP:
            flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
            break;
        case FLAGS_WINDOW_MODE_BORDERLESS:
            flags = SDL_WINDOW_BORDERLESS;
            break;
    }

    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED_DISPLAY(currentScreen), SDL_WINDOWPOS_UNDEFINED_DISPLAY(currentScreen), originalWidth, originalHeight, flags);
    if (window == nullptr) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        ERR_PRINT("error handle the window initialization\n");
        return false;
    }

    running = true;
}

Window::~Window() {
    clean();
}

void Window::set_mode(Mode mode) {
    Mode = p_mode;

    Uint32 flags = 0;

    switch (p_mode) {
        case FLAGS_WINDOW_MODE_WINDOWED:
            flags = SDL_WINDOW_SHOWN;
            break;
        case FLAGS_WINDOW_MODE_FULLSCREEN:
            flags = SDL_WINDOW_FULLSCREEN;
            break;
        case FLAGS_WINDOW_MODE_FULLSCREEN_DESKTOP:
            flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
            break;
        case FLAGS_WINDOW_MODE_BORDERLESS:
            flags = SDL_WINDOW_BORDERLESS;
            break;
    }

    SDL_SetWindowFullscreen(window, flags);
}

void Window::popup(const Vector2& p_screen_rect) {
    if (!can_draw()) {
        return;
    }

    // set the popup position based on the provided screen_rect
    SDL_SetWindowPosition(window, static_cast<int>(p_screen_rect.x), static_cast<int>(p_screen_rect.y));
}

void Window::popup_centered_ratio(float p_ratio) {
    if (!can_draw()) {
        return;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int popupWidth = static_cast<int>(windowWidth * p_ratio);
    int popupHeight = static_cast<int>(windowHeight * p_ratio);
	
	
    int popup_x = (windowWidth - popupWidth) / 2;
    int popup_y = (windowHeight - popupHeight) / 2;

    // set the popup position
    SDL_SetWindowPosition(window, popup_x, popup_y);
}

Matrix4 Window::get_screen_transform_internal(bool p_absolute_position) const {
    Matrix4 p_matrix;

    
    const float windowScaleX = 1.0f;
    const float windowScaleY = 1.0f;
    const float windowRotation = 0.0f;

    transformationMatrix.elements[0][0] = windowScaleX;
    transformationMatrix.elements[1][1] = windowScaleY;

    
    float cosTheta = std::cos(windowRotation);
    float sinTheta = std::sin(windowRotation);
    transformationMatrix.elements[0][0] = cosTheta;
    transformationMatrix.elements[0][1] = -sinTheta;
    transformationMatrix.elements[1][0] = sinTheta;
    transformationMatrix.elements[1][1] = cosTheta;

    if (p_absolute_position) {
       	return;
    }

    return p_matrix;
}

void Window::show() {
    SDL_ShowWindow(window);
    visible = true;
}

void Window::hide() {
    SDL_HideWindow(window);
    visible = false;
}

bool Window::is_visible() const {
    return visible;
}

void Window::set_visible(bool isVisible) {
    if (isVisible) {
        show();
    } else {
        hide();
    }
}

void Window::update_mouse_cursor_state() {
    SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
}

bool Window::is_maximize_allowed() const {
    return (SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED) == 0;
}

bool Window::can_draw() const {
    return (window != nullptr) && (renderer != nullptr);
}

const char* Window::get_title() const {
    return SDL_GetWindowTitle(window);
}

std::pair<int, int> Window::get_size() const {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    return std::make_pair(width, height);
}

std::pair<int, int> Window::get_size_with_decorations() const {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    return std::make_pair(width, height);
}

std::pair<int, int> Window::get_position() const {
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    return std::make_pair(x, y);
}



void Window::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::is_init() const {
    return running;
}

void Window::close() {
    running = false;
}

void Window::set_title(const char* title) {
    SDL_SetWindowTitle(window, title);
}

void Window::set_size(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

void Window::reset_size() {
    SDL_SetWindowSize(window, originalWidth, originalHeight);
}

void Window::move_to_center() {
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(currentScreen), SDL_WINDOWPOS_CENTERED_DISPLAY(currentScreen));
}

Uint32 Window::get_flags() const {
    return SDL_GetWindowFlags(window);
}

int Window::get_current_screen() const {
    return currentScreen;
}

void Window::set_current_screen(int screenIndex) {
    currentScreen = screenIndex;
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_UNDEFINED_DISPLAY(currentScreen), SDL_WINDOWPOS_UNDEFINED_DISPLAY(currentScreen));
}
 
void Window::_bind_method() {
	Class::bind_method("init", &Window::init);
	Class:bind_method("set_title", "title", & Window::set_title);
}
