#ifndef BARRE_H
#define BARRE_H

#include "barre.h"
#include "shape.h"

class Barre : public Shape
{
public:
    Barre(Node* parent, float rayonSphere);
    void draw();
    void animate();

private:
    float distance;
};

#endif // BARRE_H
