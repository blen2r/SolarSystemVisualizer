#include "texture.h"
#include "optionsholder.h"

Texture::Texture(Node* parent, string filePath,bool emitLight) : Node(parent)
{
    quadric=gluNewQuadric();
    gluQuadricTexture(quadric, GLU_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    image = QGLWidget::convertToGLFormat(QImage(filePath.c_str()));

    this->emitLight = emitLight;

    glDeleteTextures(2, texture);
    glEnable(GL_TEXTURE_2D);

    gluQuadricTexture(quadric, GLU_TRUE);

    // cette etape est peut etre inutile. A confirmer.
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                  GL_RGBA,           // internal texture storage format
                  image.width(),     // texture width
                  image.height(),    // texture height
                  GL_RGBA,           // pixel format
                  GL_UNSIGNED_BYTE,  // color component format
                  image.bits());     // pointer to texture image

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGBA,
                image.width(),
                image.height(),
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                image.bits());


}

GLUquadricObj* Texture::getQuadric()
{
    return quadric;
}

void Texture::setQuadric(GLUquadricObj* quadric)
{
    this->quadric = quadric;
}

void Texture::doAction()
{

    glEnable(GL_TEXTURE_2D);


    if(OptionsHolder::getInstance()->getTextures())
    {
        if(OptionsHolder::getInstance()->getMin() == GL_LINEAR_MIPMAP_LINEAR)
        {
            glBindTexture(GL_TEXTURE_2D, texture[0]);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OptionsHolder::getInstance()->getMin());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OptionsHolder::getInstance()->getMag());
        }else
        {
            glBindTexture(GL_TEXTURE_2D, texture[1]);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, OptionsHolder::getInstance()->getMin());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, OptionsHolder::getInstance()->getMag());
        }
    }


    if(this->emitLight && (OptionsHolder::getInstance()->getEclairage()))
    {
        GLfloat emission[] = {1,1,1};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
    else if(OptionsHolder::getInstance()->getEclairage())
    {
        GLfloat emission[] = {0.0f, 0.0f, 0.0f};
        GLfloat diffuse[] = {0.2f, 0.2f, 0.2f};
        GLfloat spec[] = {1.0f, 1.0f, 1.0f};
        GLfloat ambient[] = {0.0f, 0.0f, 0.0f};

        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    }
    else
    {
        GLfloat emission[] = {0, 0, 0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
}

void Texture::actionSequences()
{
    doAction();

    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        getChild(i)->actionSequences();
    }

    glBindTexture(GL_TEXTURE_2D, NULL); //pour pas affecter les noeuds qui ne sont pas des enfants de la texture
}
