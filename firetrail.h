#ifndef FIRETRAIL_H
#define FIRETRAIL_H

#include "shape.h"

class FireTrail : public Shape
{
public:
    FireTrail(Node* parent);
    void draw();
    void animate();
private:
    void CreateParticle(int i);
    void EvolveParticles();
    float random(int i);
    GLUquadricObj* quadric;
};

#endif // FIRETRAIL_H
