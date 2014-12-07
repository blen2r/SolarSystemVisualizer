#ifndef OPTIONSHOLDER_H
#define OPTIONSHOLDER_H

#include <qgl.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef Q_OS_WIN32
#include "GL/glut.h"
#endif
#ifdef Q_OS_MAC
#include "GLUT/glut.h"
#endif

#include <stddef.h>


//Singleton
class OptionsHolder
{
public:
    static OptionsHolder* getInstance();

    bool getTextures();
    void setTextures(bool textures);
    bool getEclairage();
    void setEclairage(bool eclairage);
    GLenum getMag();
    void setMag(GLenum mag);
    GLenum getMin();
    void setMin(GLenum min);

private:
    OptionsHolder();
    OptionsHolder(OptionsHolder const&){}
    OptionsHolder& operator=(OptionsHolder const&){}
    static OptionsHolder* instance;

    bool textures; //est-ce que les textures doivent etre affichees
    bool eclairage; //est-ce que l'eclairage doit etre affiche
    GLenum mag; //type de filtre mag
    GLenum min; //type de filtre min

};

#endif // OPTIONSHOLDER_H
