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
#ifnded RENDERER_SERVER_H
#define RENDERER_SERVER_H


#include "core/object/m_class.h"
#include "core/object/m_object.h"
#include "core/variant/variant.h"
#include "core/variant/array.h"
#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/templates/rid.h"
#include "core/typedefs.h"

class String;
class Dictionary;
class Vector2;
class Vector3;
class Texture;
class Texture2D;
class Image;
class ResourceID;


class RendererServer : public Object {
	CLASS(RendererServer , Object);

public:
        static RendererServer *singleton;

        int mm_policy = 0;
        bool render_loop_enabled = true;

public:
	static RendererServer *get_singleton();
	
	    
    virtual ResourceID texture_2d_create(const Ref<Image> &p_image) = 0;
    virtual ResourceID texture_2d_layered_create(const Vector<Ref<Image>> &p_layers, TextureLayeredType p_layered_type);
    virtual ResourceID texture_3d_create(Image::Format, int p_width, int p_height, int p_depth, bool p_mipmaps, const Vector<Ref<Image>> &p_data);
      virtual ResourceID texture_proxy_create(Variant p_base) = 0;

      virtual void texture_2d_update(Variant p_texture, const Ref<Image> &p_image, int p_layer = 0) = 0;
      virtual void texture_3d_update(Variant p_texture, const Vector<Ref<Image>> &p_data) = 0;
      virtual void texture_proxy_update(ResourceID p_texture, Variant p_proxy_to) = 0;

        
      virtual ResourceID texture_2d_placeholder_create();
      virtual ResourceID texture_2d_layered_placeholder_create(TextureLayeredType p_layered_type);
      virtual ResourceID texture_3d_placeholder_create();

      virtual Ref<Image> texture_2d_get(ResourceID p_texture) const = 0;
      virtual Ref<Image> texture_2d_layer_get(Variant p_texture, int p_layer) const = 0;
      virtual Vector<Ref<Image>> texture_3d_get(Variant p_texture) const = 0;

      virtual void texture_replace(ResourceID p_texture, Variant p_by_texture);
      virtual void texture_set_size_overVariante(ResourceID p_texture, int p_width, int p_height);
      virtual void texture_set_path(ResourceID p_texture, const String &p_path);
      virtual String texture_get_path(ResourceID p_texture) const;
    virtual Image texture_get_format(Variant p_texture) const;
      
    // Draw
    virtual void draw_cube_mesh();
    virtual void draw_shpere_mesh();
    virtual void draw_texture(Texture2D texture, int x, int y, Color tint); 
    virtual void draw_text(const char *text, int x, int y, int size, const Color& color);
    virtual void begin_drawing();
    virtual void end_drawing();
    virtual void draw_line(int x, int y, int e_x, int e_y, Color color);
    virtual void draw_circle(int x, int y, float radius, Color color);
    virtual void draw_circle_sector(Vector2 center, float radius, float angle, float p_angle, int segments, Color color);
    virtual void draw_pixel(int x, int y, Color color);
    virtual void draw_line_strip(Vector2 *points, int count, Color color);
    virtual void draw_circle_lines(Vector2 center, float radius, Color color);
    virtual void draw_rectangle(Vector2 position, Vector2 size, Color color);
    virtual void draw_rectangle_gradient_ex(Rectangle rec, Color col1, Color col2, Color col3, Color col4);
    virtual void draw_ellipse_lines(int x, int y, float h, float v, Color color);
    virtual void draw_rectangle_gradient_v(int posX, int posY, int width, int height, Color color1, Color color2);
    
    //  Check Collisions
    virtual bool check_collision_recs(Rectangle rec1, Rectangle rec2);
    virtual bool check_collision_circles(Vector2 center1, float radius1, Vector2 center2, float radius2);
    virtual bool check_collision_circle_rec(Vector2 center, float radius, Rectangle rec);
    virtual bool check_collision_point_rec(Vector2 point, Rectangle rec);
	virtual bool check_collision_point_circle(Vector2 point, Vector2 center, float radius);
	virtual bool check_collision_point_triangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);
	virtual bool check_collision_point_poly(Vector2 point, Vector2 *points, int pointCount);
	virtual bool check_collision_lines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint);
	virtual bool check_collision_point_line(Vector2 point, Vector2 p1, Vector2 p2, int threshold); 
	virtual Rectangle get_collision_rec(Rectangle rec1, Rectangle rec2); 
	

        
        
public:
	RendererServer();
	~RendererServer();
	
	
protected:
	friend class Object;
	friend class RendererViewport;
	friend class RendererScene;
	friend class RendererCanvas;
	void _bind_methods() {}



};



#endif // RENDERER_SERVER_H