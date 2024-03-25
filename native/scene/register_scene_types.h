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
#ifndef REGISTER_SCENE_TYPES_H
#define REGISTER_SCENE_TYPES_H


#include <scene/2d/animated_sprite_2d.h>
#include <scene/2d/area_2d.h>
#include <scene/2d/collision_2d.h>
#include <scene/2d/parallax_background.h>
#include <scene/2d/node_2d.h>
#include <scene/2d/sprite_2d.h>
#include <scene/2d/path_2d.h>
#include <scene/2d/rigid_body_2d.h>
#include <scene/animation/animation_player_2d.h>
#include <scene/animation/animation_player_3d.h>
#include <scene/debug/scene_debug.h>
#include <scene/gui/grid_container.h>
#include <scene/main/network_api.h>
#include <scene/main/network_peer.h>
#include <scene/main/node.h>
#include <scene/main/window.h>
#include <scene/main/timer.h>
#include <scene/main/viewport.h>

#include <core/object/m_class.h>




void register_scene_types(bool initialized) {}
void uregister_scene_types() {}




#endif // REGISTER_SCENE_TYPES_H