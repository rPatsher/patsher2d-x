#ifndef PANEL_H
#define PANEL_H


#include <core/typedefs.h>



class Panel : public Rectangle {


private:
    Rectangle panel;
    Vector2 pos;
    int width;
    int height;
    bool initalized;
    bool visible;


public:
    Panel* create(void) const;
};



#endif