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
#ifndef RENDERER_TEXTURE_ID_H
#define RENDERER_TEXTURE_ID_H


#include "core/object/ref_counted.h"
#include "core/object/m_object.h"
#include "core/string/ustring.h" 
#include "core/typedefs.h"

#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image/stb_image.h"


#include <cstdio>
#include <cstdint>

/**
	* @class RenderTextureId
	* @brief RenderTextureId class is a placeholder class used in the context of our conversation to represent an object responsible for managing a texture ID within a rendering system. It typically includes functionality to load image data, create an OpenGL texture, and handle the associated rendering processes
*/

class RenderTextureId : public RefCounted {
	CLASS(RenderTextureId , RefCounted);
public:
	RenderTextureId();
    ~RenderTextureId();

    void load_id(const char* p_file);
    void load_texture(); 
    bool has_rendered() const;
    uint32_t get_texture_id() const;

private:
    uint32_t textureId;
    bool rendered;

};


#endif // RENDERER_TEXTURE_ID_H