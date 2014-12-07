#include "sphere.h"
#include "optionsholder.h"
#include <iostream>

Sphere::Sphere(Node* parent,float radius, int subdiv, GLUquadricObj* quadric) : Shape(parent)
{
    //quadric=gluNewQuadric();
    this->quadric=quadric;

    this->rayon = radius;
    this->subdisivions = subdiv;
}

void Sphere::draw()
{
    if(quadric == NULL) //si pas de texture appliquee a la sphere
        quadric=gluNewQuadric();

    glColor3f(0.5f, 0.5f, 0.5f);

    gluSphere(quadric, rayon, subdisivions,subdisivions);
}

void Sphere::animate()
{
}

GLUquadricObj* Sphere::getQuadric()
{
    return quadric;
}

void Sphere::setQuadric(GLUquadricObj* quadric)
{
    this->quadric = quadric;
}
