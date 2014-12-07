#include "barre.h"
#include "node.h"
#include "shape.h"

Barre::Barre(Node *parent, float rayonSphere):Shape(parent)
{
    this->distance = rayonSphere;
}

void Barre::animate()
{
    // nothing to do here
}

void Barre::draw()
{
    glPushMatrix();

    // dessiner la ligne
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(0, 0, -2*distance);
    glVertex3f(0, 0,  2*distance);
    glEnd();

    glPopMatrix();
}
