#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "shape.h"
#include "glm.h"

class Vaisseau : public Shape
{
public:
    Vaisseau(Node* parent);
    void draw();
    void animate();
    void setPointsCourbe(vector<float> *pointsCourbe);
    void resetFrame();

private:
    GLMmodel* m_model;
    vector<float> pointsCourbe;
    int frame;
    int countFrame;
    GLfloat dx, dy, dz;
};

#endif // VAISSEAU_H

