#include "light.h"
#include "optionsholder.h"

Light::Light(Node* parent) : Shape(parent)
{

}

void Light::draw()
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    GLfloat lum_diffuse [] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lum_speculaire [] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat lum_position [] = { 0.0, 0.0, 0.0, 1.0};

    glLightfv ( GL_LIGHT0, GL_DIFFUSE, lum_diffuse);
    glLightfv ( GL_LIGHT0, GL_SPECULAR, lum_speculaire);
    glLightfv ( GL_LIGHT0, GL_POSITION, lum_position);
    glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f );
    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f );
    glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f );

    if(OptionsHolder::getInstance()->getEclairage()) //active seulement si eclairage est affiche
        glEnable(GL_LIGHT0);
}

void Light::animate()
{
    // nothing to do here
}
