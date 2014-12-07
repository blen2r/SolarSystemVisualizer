#ifndef SHAPE_H
#define SHAPE_H

#include "node.h"

#include <qgl.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef Q_OS_WIN32
#include "GL/glut.h"
#endif
#ifdef Q_OS_MAC
#include "GLUT/glut.h"
#endif

class Shape : public Node
{
public:
    Shape(Node* parent);
    virtual ~Shape(); //afin que les destructeurs des enfants soient appeles
    virtual void draw() = 0;
    void doAction();
};

#endif // SHAPE_H
