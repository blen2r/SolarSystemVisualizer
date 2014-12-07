#ifndef LIGHT_H
#define LIGHT_H

#include "light.h"
#include "shape.h"

class Light : public Shape
{
public:
    Light(Node* parent);
    void draw();
    void animate();

};

#endif // LIGHT_H
