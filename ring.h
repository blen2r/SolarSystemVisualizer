#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape
{
public:
    Ring(Node* parent,float externalRadius, float internalRadius);
    void draw();
    void animate();

private:
    float intRadius, extRadius;
    GLUquadricObj* quadric;
};

#endif // RING_H
