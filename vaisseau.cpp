#include "vaisseau.h"
#include <iostream>
#include <math.h>

#include "transformgroup.h"

using namespace std;

Vaisseau::Vaisseau(Node* parent) : Shape(parent)
{
    //load spaceship
    m_model = glmReadOBJ("assets/vaisseau.obj");
    frame = 0;
    countFrame = 9999;
}

void Vaisseau::draw(){
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_NORMALIZE);

    glmDraw(m_model, GLM_MATERIAL | GLM_SMOOTH);

    glPopAttrib();
}

void Vaisseau::animate(){
    //replacer le vaisseau au debut quand il arrive a la fin
    if(frame >= pointsCourbe.size()){
        frame = 0;
    }

    //countFrame ralentit le vaisseau un peu
    if(frame < pointsCourbe.size() && countFrame >= 2)
    {
        //aligner vaisseau vers l'avant
        if(frame+3 < pointsCourbe.size())
        {
            GLfloat dx = pointsCourbe.at(frame+3) - pointsCourbe.at(frame);
            GLfloat dy = pointsCourbe.at(frame+4) - pointsCourbe.at(frame+1);
            GLfloat dz = pointsCourbe.at(frame+5) - pointsCourbe.at(frame+2);

            GLfloat hyp = sqrt((dx*dx)+(dy*dy)+(dz*dz));

            GLfloat angleAxeX = acos(dx/hyp);
            GLfloat angleAxeY = acos(dy/hyp);
            GLfloat angleAxeZ = acos(dz/hyp);

            GLfloat PI = 3.141592653589793;
            this->dx = angleAxeX* 180.0 / PI;
            this->dy = angleAxeY* 180.0 / PI;
            this->dz = angleAxeZ* 180.0 / PI;

        ((TransformGroup*)parent->getParent())->setXTrans(pointsCourbe.at(frame));
        ((TransformGroup*)parent->getParent())->setYTrans(pointsCourbe.at(frame+1));
        ((TransformGroup*)parent->getParent())->setZTrans(pointsCourbe.at(frame+2));

        //les dx et dy representent les angles pour aligner un axe, donc doit faire rotation autour d'un autre axe!
        if(dz < 0)
            ((TransformGroup*)parent)->setYRot(this->dx);
        else
            ((TransformGroup*)parent)->setYRot(360.0f - this->dx);

        ((TransformGroup*)parent)->setZRot(360.0f - this->dy);

        }

        frame+=3;
        countFrame = 0;
    }

    countFrame++;
}

void Vaisseau::setPointsCourbe(vector<float> *pointsCourbe)
{
    this->pointsCourbe.clear();
    this->pointsCourbe.insert(this->pointsCourbe.end(), pointsCourbe->begin(), pointsCourbe->end());
}

void Vaisseau::resetFrame()
{
    frame = 0;
    countFrame = 9999;
}
