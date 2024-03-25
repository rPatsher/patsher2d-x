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
#ifndef NODE_H
#define NODE_H

#include <core/object/ref_counted.h>
#include <core/object/m_class.h>
#include <core/object/m_object.h>

#include <cstring.h>
#include <cmath>
#include <cstdint>
#include <cstdio>

class Camera;
class Camera2D;
class RendererServer;
class Grid2D;
class Action;
class PhysicsBody;
class Scene;

/** @class Node
* @brief Node is the base element of the Scene Graph. Elements of the Scene Graph must be Node objects or subclasses of it.
 The most common Node objects are: Scene, Layer, Sprite, Menu, Label.

 The main features of a Node are:
 - They can contain other Node objects (`addChild`, `getChildByTag`, `removeChild`, etc)
 - They can schedule periodic callback (`schedule`, `unschedule`, etc)
 - They can execute actions (`runAction`, `stopAction`, etc)

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding `draw` to render the node

 Properties of Node:
 - position (default: x=0, y=0)
 - scale (default: x=1, y=1)
 - rotation (in degrees, clockwise) (default: 0)
 - anchor point (default: x=0, y=0)
 - contentSize (default: width=0, height=0)
 - visible (default: true)

 Limitations:
 - A Node is a "void" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass Node and override `draw`.

 */
class Node : public Object {
    CLASS(Node , Object);
    

public:
    enum State {
        OBJ_NODE_ON_ENTER,
        OBJ_NODE_ON_EXIT,
        OBJ_NODE_ON_FINSHID,
        OBJ_NODE_ON_CLEANUP,
        OBJ_NODE_ON_START
    };
    enum Flags {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
        FLAGS_RENDER_AS_3D = (1 << 3),
        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };


protected:
    float _local;
    float _rotationX; // Rotation on the X-axis
    float _rotationY; // Rotation on the Y-axis

public:
    virtual void set_local_zorder(const int32_t p_local);
   virtual void _set_local_zorder(const int32_t z);
   void update();
   virtual int32_t get_local_z() { return; }
   virtual void set_global_order(float global);
    static const int INVALID_TAGS = -1;
    static int get_attached_node_count(); // Gets count of nodes those are attached to scene graph 
    virtual void set_scale_x(float scale_x);
    virtual float get_scale_x() const;
    virtual void set_scale_y(float scale_y);
    virtual float get_scale_y() const;
    
    // Node Group 
    
    void add_to_group(const StringName &p_identifier, bool p_persistent = false);
	void remove_from_group(const StringName &p_identifier);
	bool is_in_group(const StringName &p_identifier) const;
	// Scene Tree 
	void add_child_helper(Node child ,int tag ,float local , bool set_tag , const char* name);
	void add_child(Node *p_child, bool p_legible_unique_name = false);
	void add_child_below_node(Node *p_node, Node *p_child, bool p_legible_unique_name = false);
	void remove_child(Node *p_child);
	
	
	


protected:
	// 


public:
    Node();
    virtual ~Node();

};



#endif // NODE_H
