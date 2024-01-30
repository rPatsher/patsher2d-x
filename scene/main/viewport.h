





#ifndef VIEWPORT_H
#define VIEWPORT_H




#include <scene/main/node.h>
#include <core/object/m_class.h>
#include <core/object/ref_counted.h>
#include <core/templates/hash_map.h>
#include <core/templates/vector.h>

#include <cstdint>
#include <cstdlib>

class Viewport : public Node {
    MCLASS(Viewport , Node);
};



#endif // VIEWPORT_H