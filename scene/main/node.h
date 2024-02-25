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


private:
    void add_child_helper(const Ref<Node> child,int tag ,float local , bool set_tag , const char* name);    


protected:
    float _local;
    float _rotationX; // Rotation on the X-axis
    float _rotationY; // Rotation on the Y-axis

public:
    static const int INVALID_TAGS = -1;
    static Node* create(void); // For create a default instance

    static int get_attached_node_count(); // Gets count of nodes those are attached to scene graph 
    /**
     * The Node's parent will sort all its children based on the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOrder values < 0 are the "left" subtree
     While Nodes with LocalZOrder >=0 are the "right" subtree.
    */

    virtual void set_local_zorder(const int32_t p_local);
    /**
     Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
    */
   
   virtual void _set_local_zorder(const int32_t z);

    /** !!! ONLY FOR INTERNAL USE
    * Sets the arrival order when this node has a same ZOrder with other children.
    *
    * A node which called addChild subsequently will take a larger arrival order,
    * If two children have the same Z order, the child with larger arrival order will be drawn later.
    *
    * @warning This method is used internally for localZOrder sorting, don't change this manually
    *
    * @param up   The arrival order.
    */

   void update();

   /**
     * Gets the local Z order of this node.
     *
     * @see `setLocalZOrder(int)`
     *
     * @return The local (relative to its siblings) Z order.
     */

    virtual int32_t get_local_z() { return; }

    /**
     Defines the order in which the nodes are renderer.
     Nodes that have a Global Z Order lower, are renderer first.
     
     In case two or more nodes have the same Global Z Order, the order is not guaranteed.
     The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
     
     By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.
     
     Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
     
     Limitations: Global Z Order can't be used by Nodes that have SpriteBatchNode as one of their ancestors.
     And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.

     @see `setLocalZOrder()`
     @see `setVertexZ()`

     @since v3.0
     *
     * @param global The global Z order value.
     */
    virtual void set_global_order(float global);
     /**
     * Sets the scale (x) of the node.
     *
     * It is a scaling factor that multiplies the width of the node and its children.
     *
     * @param scale_x   The scale factor on X axis.
     */
    virtual void set_scale_x(float scale_x);
     /**
     * Returns the scale factor on X axis of this node
     *
     * @see set_scale_x(float)
     *
     * @return The scale factor on X axis.
     */
    virtual float get_scale_x() const;
    /**
     * Sets the scale (y) of the node.
     *
     * It is a scaling factor that multiplies the height of the node and its children.
     *
     * @param scale_y   The scale factor on Y axis.
     */
    virtual void set_scale_y(float scale_y);
     /**
     * Returns the scale factor on Y axis of this node
     *
     * @see `set_scale_y(float)`
     *
     * @return The scale factor on Y axis.
     */
    virtual float get_scale_y() const;


protected:
	// 


public:
    Node();
    virtual ~Node();

};



#endif // NODE_H
