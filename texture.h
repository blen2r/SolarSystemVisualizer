#ifndef TEXTURE_H
#define TEXTURE_H

#include "node.h"

#include <qgl.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef Q_OS_WIN32
#include "GL/glut.h"
#endif
#ifdef Q_OS_MAC
#include "GLUT/glut.h"
#endif

#include <string>
using namespace std;

class Texture : public Node
{
public:
    Texture(Node* parent, string filePath,bool emitLight=false);
    GLUquadricObj* getQuadric();
    void setQuadric(GLUquadricObj* quadric);
    void doAction();
    void actionSequences();

private:
    GLuint texture[2];
    GLUquadricObj* quadric;
    QImage image;
    bool emitLight; //est-ce que la texture est appliquee a un objet qui emet de la lumiere?
};

#endif // TEXTURE_H
