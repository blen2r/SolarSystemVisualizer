#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere(Node* parent,float radius, int subdiv, GLUquadricObj* quadric=NULL);
    void draw();
    void animate();
    GLUquadricObj* getQuadric();
    void setQuadric(GLUquadricObj* quadric);

private:
    GLUquadricObj* quadric;
    float rayon;
    int subdisivions;
};

#endif // SPHERE_H
