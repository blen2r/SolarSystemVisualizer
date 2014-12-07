#include "ring.h"

#include <math.h>
#include <iostream>

Ring::Ring(Node* parent, float externalRadius, float internalRadius): Shape(parent)
{
    this->intRadius = internalRadius;
    this->extRadius = externalRadius;
    this->quadric = gluNewQuadric();
}

// source pour le ring: http://www.opengl.org/sdk/docs/man2/xhtml/gluPartialDisk.xml (4 nov 2013)
void Ring::draw()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, NULL);

  //  glColor3f(1.0, 1.0, 1.0);
    gluPartialDisk(this->quadric,this->intRadius,this->extRadius, 25, 25, 0, 360);

    glPopMatrix();
}

void Ring::animate()
{
    // nothing to do here.
}
