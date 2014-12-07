#ifndef TRANSFORMGROUP_H
#define TRANSFORMGROUP_H

#include "node.h"

#include <qgl.h>

class TransformGroup : public Node
{
public:
    TransformGroup(Node* parent);
    ~TransformGroup();

    GLfloat getXTrans();
    GLfloat getYTrans();
    GLfloat getZTrans();
    void setXTrans(GLfloat x);
    void setYTrans(GLfloat y);
    void setZTrans(GLfloat z);

    GLfloat getXScale();
    GLfloat getYScale();
    GLfloat getZScale();
    void setXScale(GLfloat xScale);
    void setYScale(GLfloat yScale);
    void setZScale(GLfloat zScale);

    GLfloat getXRot();
    GLfloat getXIncrement();
    void setXRot(GLfloat xRot);
    void setXIncrement(GLfloat xIncrement);
    GLfloat getYRot();
    GLfloat getYIncrement();
    void setYRot(GLfloat yRot);
    void setYIncrement(GLfloat yIncrement);
    GLfloat getZRot();
    GLfloat getZIncrement();
    void setZRot(GLfloat zRot);
    void setZIncrement(GLfloat zIncrement);

    void setName(string name);
    string getName();

    void transform();
    void doAction();
    void actionSequences();
    void animate();

   // virtual void animate()=0;

protected:
    GLfloat xTrans, yTrans, zTrans;
    GLfloat xScale, yScale, zScale;
    GLfloat xRot, xIncrement, yRot, yIncrement, zRot, zIncrement;
    int rotations=0;
    string name = "";
};

#endif // TRANSFORMGROUP_H
