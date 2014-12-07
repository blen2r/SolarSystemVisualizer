#include "transformgroup.h"

#include <iostream>
using namespace std;

TransformGroup::TransformGroup(Node* parent) : Node(parent)
{
    xTrans = yTrans = zTrans = xRot = xIncrement = yRot = yIncrement = zRot = zIncrement = 0.0f;
    xScale = yScale = zScale = 1.0f;
}

TransformGroup::~TransformGroup()
{
}

GLfloat TransformGroup::getXTrans()
{
    return xTrans;
}

GLfloat TransformGroup::getYTrans()
{
    return yTrans;
}

GLfloat TransformGroup::getZTrans()
{
    return zTrans;
}

void TransformGroup::setXTrans(GLfloat x)
{
    xTrans = x;
}

void TransformGroup::setYTrans(GLfloat y)
{
    yTrans = y;
}

void TransformGroup::setZTrans(GLfloat z)
{
    zTrans = z;
}

void TransformGroup::transform()
{
    if(xScale != 1.0f || yScale != 1.0f || zScale != 1.0f)
        glScalef(xScale, yScale, zScale);

    if(xRot != 0.0f)
        glRotatef(xRot, 1.0f , 0.0f , 0.0f);

    if(yRot != 0.0f)
        glRotatef(yRot, 0.0f , 1.0f , 0.0f);

    if(zRot != 0.0f)
        glRotatef(zRot, 0.0f , 0.0f , 1.0f);

    if(xTrans != 0.0f || yTrans != 0.0f || zTrans != 0.0f)
        glTranslatef(xTrans, yTrans, zTrans);

}

void TransformGroup::doAction()
{
    transform();
}

void TransformGroup::actionSequences()
{
    glPushMatrix();

    doAction();

    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        getChild(i)->actionSequences();
    }

    glPopMatrix();
}

void TransformGroup::animate()
{
    xRot += xIncrement;
    if(xRot >= 360.0f)
        xRot = 0.0f;
    else if(xRot < 0.0f)
        xRot = 360.0f;

    yRot += yIncrement;
    if(yRot >= 360.0f)
        yRot = 0.0f;
    else if(yRot < 0.0f)
        yRot = 360.0f;

    zRot += zIncrement;
    if(zRot >= 360.0f)
    {
        zRot = 0.0f;

        //code qui affiche combien de jours sont dans une annee pour chaque astre
        /*if(this->name.compare("photonJour") == 0 || this->name.compare("orionJour") == 0 || this->name.compare("sateliteOrbite") == 0)
        {
            this->rotations++;
            cout << this->name;
            cout << " : ";
            cout << this->rotations;
            cout << "\n";
        }

        if(this->name.compare("photonAnnee") == 0)
        {
            cout << "1 an PHOTON\n";
        }

        if(this->name.compare("orionAnnee") == 0)
        {
            cout << "1 an ORION\n";
        }

        if(this->name.compare("cometeAnnee") == 0)
        {
            cout << "1 an COMETE\n";
        }*/

    }else if(zRot < 0.0f)
    {
        zRot = 360.0f;

        //code qui affiche combien de jours sont dans une annee pour chaque astre
        /*if(this->name.compare("photonJour") == 0 || this->name.compare("orionJour") == 0 || this->name.compare("sateliteOrbite") == 0)
        {
            this->rotations++;
            cout << this->name;
            cout << " : ";
            cout << this->rotations;
            cout << "\n";
        }

        if(this->name.compare("photonAnnee") == 0)
        {
            cout << "1 an PHOTON\n";
        }

        if(this->name.compare("orionAnnee") == 0)
        {
            cout << "1 an ORION\n";
        }

        if(this->name.compare("cometeAnnee") == 0)
        {
            cout << "1 an COMETE\n";
        }*/
    }


    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        getChild(i)->animate();
    }
}

GLfloat TransformGroup::getXRot()
{
    return xRot;
}

GLfloat TransformGroup::getXIncrement()
{
    return xIncrement;
}

void TransformGroup::setXRot(GLfloat xRot)
{
    this->xRot = xRot;
}

void TransformGroup::setXIncrement(GLfloat xIncrement)
{
    this->xIncrement = xIncrement;
}

GLfloat TransformGroup::getYRot()
{
    return yRot;
}

GLfloat TransformGroup::getYIncrement()
{
    return yIncrement;
}

void TransformGroup::setYRot(GLfloat yRot)
{
    this->yRot = yRot;
}

void TransformGroup::setYIncrement(GLfloat yIncrement)
{
    this->yIncrement = yIncrement;
}

GLfloat TransformGroup::getZRot()
{
    return zRot;
}

GLfloat TransformGroup::getZIncrement()
{
    return zIncrement;
}

void TransformGroup::setZRot(GLfloat zRot)
{
    this->zRot = zRot;
}

void TransformGroup::setZIncrement(GLfloat zIncrement)
{
    this->zIncrement = zIncrement;
}

GLfloat TransformGroup::getXScale()
{
    return xScale;
}

GLfloat TransformGroup::getYScale()
{
    return yScale;
}

GLfloat TransformGroup::getZScale()
{
    return zScale;
}

void TransformGroup::setXScale(GLfloat xScale)
{
    this->xScale = xScale;
}

void TransformGroup::setYScale(GLfloat yScale)
{
    this->yScale = yScale;
}

void TransformGroup::setZScale(GLfloat zScale)
{
    this->zScale = zScale;
}

void TransformGroup::setName(string name)
{
    this->name = name;
}

string TransformGroup::getName()
{
    return this->name;
}
