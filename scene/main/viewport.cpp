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
#include "viewport.h"

#include "core/input/input.h"
#include "core/object/m_object.h"
#include "core/object/ref_counted.h"
#include "core/math/transform_2d.h"
#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/io/resources.h"
#include "scene/resources/texture.h"
#include "servers/renderer/rendere_texture_id.h"
#include "core/typedefs.h"


Viewport::Viewport() {
        // Set default values for members
        mode = Mode::VIEWPORT_2D_MODE;
        is_2d_enabled = true;
        is_3d_enabled = true;
}
Viewport::~Viewport() {

}
Matrix Viewport::get_final_transform() const {
    Matrix finalTransform = get_camera_2d(); 
    return finalTransform;
}
Vector2 Viewport::get_minimum_size() const {
        if (has_minimum_size) {
            return minimum_size;
        }
        Vector2 minSize;
        return minSize;
}

Vector2 Viewport::get_maximum_size() const {
        if (has_maximum_size) {
            return maximum_size;
        }
        Vector2 maxSize;
        return maxSize;
    }

void Viewport::begin_drawing() {
    if (mode == Mode::VIEWPORT_2D_MODE) {
        BeginMode2D(camera2d);
        ClearBackground(clear_background_color);

        // Draw 2D grid using camera2d
        Vector2 screenCenter = GetScreenCenter();
        float cellSize = gridSize; // Adjust grid cell size
        int numCellsX = (int)ceil(get_visible_rect().width / cellSize);
        int numCellsY = (int)ceil(get_visible_rect().height / cellSize);

        for (int x = -numCellsX / 2; x <= numCellsX / 2; ++x) {
            for (int y = -numCellsY / 2; y <= numCellsY / 2; ++y) {
                Vector2 worldPos = {screenCenter.x + x * cellSize, screenCenter.y + y * cellSize};
                Vector2 screenPos = GetWorldToScreen2D(worldPos, camera2d);
                DrawLineEx(Vector2Int(screenPos.x, screenPos.y) - gridLineThickness / 2,
                           Vector2Int(screenPos.x, screenPos.y) + gridLineThickness / 2,
                           gridLineThickness, gridLineColor);
            }
        }
        if (is_rendering_enabled && is_2d_enabled) {
        	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                float zoomAmount = GetMouseWheelMove();
                camera2d.target.x += zoomAmount * camera2d.offset.x;
                camera2d.target.y += zoomAmount * camera2d.offset.y;
                
                // Display mouse position and zoom text
                Vector2 screenMousePos = GetMousePosition();
                Vector2 worldMousePos = GetScreenToWorld2D(screenMousePos, camera2d);

                // Calculate bottom left position based on viewport dimensions
                int viewportWidth = GetScreenWidth() / 2; 
                int viewportHeight = GetScreenHeight() / 2;
                Vector2 textPosition = { 10, viewportHeight - 30 }; // Add left and bottom margin
                DrawTextFormatted(
                    TextFormat("%s: %.1f\nZoom Size: %.2f",
                             "Mouse Position:", worldMousePos.x, zoomAmount),
                    textPosition.x, textPosition.y, 20, WHITE
                );
            } else if {
            // Border dimensions and color
            int borderThickness = 5; 
            Color borderColor = BLACK;
            // Background rectangle
            Rectangle backgroundRect = { 0, 0, GetScreenWidth(), GetScreenHeight() }; // Assumes full-screen viewport
            DrawRectangleRec(backgroundRect, BLACK);
            Rectangle viewportRect = {
                camera2d.offset.x, camera2d.offset.y,
                GetScreenWidth() - camera2d.offset.x * 2, GetScreenHeight() - camera2d.offset.y * 2
            };

            // Draw viewport border lines
            DrawLineEx(viewportRect.min.x, viewportRect.min.y, viewportRect.min.x, viewportRect.max.y, borderThickness, borderColor);
            DrawLineEx(viewportRect.max.x, viewportRect.min.y, viewportRect.max.x, viewportRect.max.y, borderThickness, borderColor);
            DrawLineEx(viewportRect.min.x, viewportRect.min.y, viewportRect.max.x, viewportRect.min.y, borderThickness, borderColor);
            DrawLineEx(viewportRect.min.x, viewportRect.max.y, viewportRect.max.x, viewportRect.max.y, borderThickness, borderColor);
        }
    }
  } else if {
  		if (mode == Mode::VIEWPORT_3D_MODE) {
  			if (texture) {
            BeginTextureMode(texture);
        }
        SetViewport(get_visible_rect());
        ClearBackground(BLACK);

        BeginMode3D(camera3d); // Set up 3D camera
        EnableDepthTest(); // Enable depth testing for 3D

        // Draw grid using camera3d and projection
        Matrix projection = GetCameraProjection(camera3d);
        Vector3 gridLines[4] = {
            {gridSize, 0.0f, 0.0f},
            {-gridSize, 0.0f, 0.0f},
            {0.0f, gridSize, 0.0f},
            {0.0f, -gridSize, 0.0f},
        };

        for (int i = 0; i < 4; ++i) {
            Vector3 worldLine[2] = {gridLines[i], gridLines[i]};
            Vector3 screenLine[2];

            for (int j = 0; j < 2; ++j) {
                Vector3 transformed = MatrixMultiplyVector(projection, worldLine[j]);
                transformed.x /= transformed.w;
                transformed.y /= transformed.w;
                screenLine[j] = transformed;
            }

            DrawLineEx(Vector2Int(screenLine[0].x, screenLine[0].y), Vector2Int(screenLine[1].x, screenLine[1].y), 1.0f, LIGHTGRAY);
        }
  			
  }
  }
  
  
  
  
}



bool Viewport::find_world_2d(Vector2 screenPos, float* zPos) {
    if (!CheckCollisionPointRec(screenPos, bounds)) {
        return false; // Click outside viewport
    }

    // Assuming a 2D plane at z = 0
    Ray ray = GetMouseRayDirection(screenPos, camera);
    float denominator = ray.direction.z;
    if (fabs(denominator) < FLT_EPSILON) {
        return false; // Ray parallel to plane
    }

    float t = -(ray.origin.z) / denominator;
    if (t < 0.0f) {
        return false; // Ray points away from plane
    }

    Vector3 worldPos = ray.origin + t * ray.direction;
    if (zPos) {
        *zPos = worldPos.z;
    }
    

Matrix Viewport::get_camera_2d() const {
    // Return the 2D camera transformation based on your 3D camera and viewport
    Vector3 camPos = camera.position;
    Vector3 camUp = camera.up;
    Vector3 camTarget = camera.target;

    float left = camPos.x - width / 2.0f;
    float right = left + width;
    float bottom = camPos.y - height / 2.0f;
    float top = bottom + height;

    Matrix projection = Orthographic(left, right, bottom, top, -100.0f, 100.0f);
    Matrix view = LookAt(camPos, camTarget, camUp);

    return projection * view;
}

unsigned int Viewport::get_canvas_cull_mask_bit(int layer) const {
    if (layer < 0 || layer >= MAX_CANVAS_LAYERS) {
        return 0; 
    }
    return 1 << layer;
}
void Viewport::BeginDrawing() {
    BeginTextureMode(texture);
    SetViewport(bounds);
}

void Viewport::EndDrawing() {
    EndTextureMode();
}

Texture* Viewport::get_texture() const {
    return texture;
}

Vector2 Viewport::get_mouse_position() const {
    return GetMousePosition();
}

Rectangle Viewport::get_visible_rect() const {
    return bounds;
}

RenderTextureId Viewport::get_viewport_rid() const {
    return renderTextureId;
}

void Viewport::begin_drawing_with_border(Color borderColor, int p_int) {
    BeginTextureMode(texture);
    SetViewport(get_visible_rect());
    draw_border(borderColor, p_int); 
}

void Viewport::set_size(int newWidth, int newHeight) {
    // Validate new dimensions to avoid potential issues
    if (newWidth > 0 && newHeight > 0) {
        width = newWidth;
        height = newHeight;
        bounds = { center.x - width / 2.0f, center.y - height / 2.0f, width, height };
    } else {
        ERR_PRINT("Viewport::set_size(): Invalid dimensions provided. Width and height must be positive\n");
    }
}

Rectangle Viewport::get_size() const {
    return { center.x - width / 2.0f, center.y - height / 2.0f, width, height };
}


void Viewport::draw_border(Color borderColor, int p_int) {
    Rectangle borderRect = get_visible_rect();
    borderRect.x -= p_int / 2;
    borderRect.y -= p_int / 2;
    borderRect.width += p_int;
    borderRect.height += p_int;

    DrawRectangleLinesEx(borderRect, p_int, borderColor);
}

void Viewport::handle_text_input() {
        if (Input::get_singleton()->is_key_pressed(Key::KEY_BACKSPACE)) {
        } else if (Input::get_singleton()->is_key_pressed(Key::KEY_ENTER)) {
            // Handle enter
            ERR_WARN("\n");
        } else {
            char ch = GetCharPressed();
            if (ch >= 32 && ch <= 126) { // Check for printable characters
            	ERR_WARN("\n", ch);
            
            }
        }
}
bool Viewport::find_world_3d(Vector2 screenPos, Ray* outRay, std::function<bool(const Ray&, HitInfo&)> callback) {
    if (!CheckCollisionPointRec(screenPos, bounds)) {
        return false; // Click outside viewport
    }

    Vector3 worldPos = GetScreenToWorldEx(screenPos, camera);
    Vector3 dir = GetMouseRayDirection(screenPos, camera);

    *outRay = Ray(worldPos, dir);

    HitInfo hitInfo;
    bool hit = GetRayCollisionEx(*outRay, INFINITY, &hitInfo);
    if (hit && callback(*outRay, hitInfo)) {
        return true;
        ERR_WARN("successful raycast and callback\n");
    }

    return false; 
    ERR_WARN("no hit or callback failed\n");
    
	}
}

Color ViewportTexture::get_tint() const {
    return tint;
}

float ViewportTexture::get_rotation() const {
    return rotation;
}
float ViewportTexture::get_scale() const {
    return scale;
}

Texture* ViewportTexture::get_texture() const {
    return texture;
}

void ViewportTexture::set_source_rect_from_texture() {
    if (texture) {
        sourceRect.width = texture->width;
        sourceRect.height = texture->height;
    }
}

void ViewportTexture::draw(Viewport& viewport) {
    if (texture && viewport.is_rendering_enabled) {
        Rectangle targetRect = {
            viewport.camera2d.offset.x + position.x,
            viewport.camera2d.offset.y + position.y,
            sourceRect.width * scale,
            sourceRect.height * scale
        };

        DrawTextureEx(
            *texture,
            sourceRect,
            targetRect,
            rotation,
            scale,
            tint
        );
    }
}


void ViewportTexture::set_position(Vector2 position) {
    this->position = position;
}

void ViewportTexture::set_rotation(float rotation) {
    this->rotation = rotation;
}

void ViewportTexture::set_scale(float scale) {
    this->scale = scale;
}

void ViewportTexture::set_tint(Color tint) {
    this->tint = tint;
}

void CameraViewport::set_size(Rectangle newViewport) {
    if (is_active) {
        viewport = newViewport;
    }
}


void CameraViewport::set_camera(const Camera2D& camera) {
    this->camera = camera;
}

void CameraViewport::begin_drawing() {
    if (is_active) {
        BeginMode2D(camera);   
    } else {
    	EndMode2D();
    }
}

void CameraViewport::end_drawing() {
    if (is_active) {
        EndMode2D();
    }
}


void CameraViewport::set_target(RenderTexture2D* target) {
    if (is_active) {
        if (target) {
            BeginTextureMode(*target);
            BeginMode2D(camera);
        } else {
            EndTextureMode();
            BeginMode2D(camera); // Switch back to default framebuffer
        }
    }
}

void CameraViewport::_bind_methods() {
	Class::bind_method("set_target", "target" &CameraViewport::set_target);
	Class::bind_method("set_tint", "tint", &Camera::set_tint);
	Class::bind_method("set_camera", "camera", &CameraViewport::set_camera);
	Class::bind_method("set_scale", "scale", &CameraViewport::set_scale);
	Class::bind_method("set_position", "position", &CameraViewport::set_position);
	Class::bind_method("begin_drawing", &CameraViewport::begin_drawing);
	Class::bind_method("end_drawing", &CameraViewport::end_drawing);
	Class::bind_method("get_scale", &CameraViewport::get_scale);
	Class::bind_method("get_rotation", &CameraViewport::get_rotation);
	Class::bind_method("set_source_rect_from_texture", & CameraViewport::set_source_rect_from_texture);
}