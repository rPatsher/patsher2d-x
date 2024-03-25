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

#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "scene/main/node.h"
#include "core/templates/hash_map.h"
#include "core/templates/map.h"
#include "core/templates/vector.h"
#include "core/object/ref_counted.h"
#include "core/object/m_object.h"
#include "core/error/error_macros.h"


class Transform2D;
class Resource;
class Vector2;
class Vector3;
class Camera2D;
class Camera3D;
struct Rectangle;
class Texture2D;
class Texture;

class RenderTextureId;

#include <cstdint>
#include <cstdlib>

/**
	* @class Viewport
	* @brief Viewport class is a tool used in game development and graphics applications to manage specific areas within the main rendering output. It acts as a virtual window or camera within the larger display, allowing you to control what and how things are presented within its defined boundaries
*/

class Viewport : public Node {
    CLASS(Viewport , Node);
public:
	enum Mode {
    	VIEWPORT_2D_MODE,
    	VIEWPORT_3D_MODE
    };
public:
	Vector2 get_minimum_size() const;
	void set_enabled_3d_mode(bool enabled);
	void set_enabled_2d_mode(bool enabled);
	Vector2 get_view_targert(const Vector3& world_position) const;
	
	// Drawing

	void draw_border(Color borderColor, int p_int);
	void draw_texture_rect(Ref<Texture2D> texture, Rectangle source_rect, Vector2 position, float rotation = 0.0f, float scale = 1.0f, Color tint);
	void draw_texture(Texture* texture, Vector2 position, float rotation = 0.0f, float scale = 1.0f, Color tint);
	void set_clear_background_color(Color color);
	Color get_clear_background_color();
	void set_size(int p_width, int p_height);
	Rectangle get_size() const;
	const Camera3D& get_camera_3d() const { return camera; }
    Matrix get_camera_2d() const;
    Matrix get_final_transform() const;
    unsigned int get_canvas_cull_mask_bit(int layer) const;
    Texture* get_texture() const;
    Vector2 get_mouse_position() const;
    Rectangle get_visible_rect() const;
    RenderTextureId get_viewport_rid() const;
    
    // Input
    void process_mouse_input(Vector2 mouse_position);
    Matrix get_screen_transform() const;

public:
	void begin_drawing();
	void end_drawing();
	void begin_drawing_with_border(Color color , int p_int);
	Viewport();
	~Viewport();
private:
	Camera2D camera2d;
	Camera3D camera;
    Vector2 scrollSpeed = {5.0f, 5.0f}; // Scrolling speed
    bool allowScrollDown = true;
    bool allowScrollRight = true;
    bool allowScrollLeft = true;
    bool allowScrollTop = true;
	bool is_2d_enabled = true;
    bool is_3d_enabled = true;
    bool gui_is_dragging = false; // Track dragging state
Vector2 initial_mouse_pos; // Store initial mouse position

    float width;
    float height;
    Rectangle bounds;
    Texture* texture;
    RenderTextureId renderTextureId;
    
	
};

/** 
	* @class ViewportTexture 
	* @brief ViewportTexture class wouldn't be part of the core PatsherEngine functionality. However, you can create a custom ViewportTexture class to represent textures that are associated with specific viewports and can be drawn within those viewports
*/

class ViewportTexture : public Viewport { 
	CLASS(ViewportTexture , Viewport);

public:
	void set_texture(Texture* texture);
    void set_source_rect(Rectangle sourceRect);
    void set_position(Vector2 position);
    void set_rotation(float rotation);
    void set_scale(float scale);
    void set_tint(Color tint);
    void draw(Viewport& viewport);

private:
    Texture* texture;
    Rectangle sourceRect;
    Vector2 position;
    float rotation;
    float scale;
    Color tint;
};

/**
	* @class CameraViewport
	* @brief CameraViewport class manages a camera and its associated viewport within a project It provides functionalities for
	
*/
class CameraViewport : public Viewport {
	CLASS(CameraViewport , Viewport);
public:
    CameraViewport();
    ~CameraViewport();

    void set_camera(const Camera2D& camera);
    void set_viewport(Rectangle viewport);
    void set_active(bool active);

    void BeginDrawing();
    void EndDrawing();

private:
    Camera2D camera;
    Rectangle viewport;
    bool is_active;
};


#endif // VIEWPORT_H