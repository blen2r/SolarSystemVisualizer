#include "optionsholder.h"

OptionsHolder* OptionsHolder::instance = NULL;

OptionsHolder::OptionsHolder()
{
    eclairage = true;
    textures = true;

    mag = GL_NEAREST;
    min = GL_NEAREST;
}

OptionsHolder* OptionsHolder::getInstance()
{
    if(!instance)
        instance = new OptionsHolder();

    return instance;
}

bool OptionsHolder::getTextures()
{
    return textures;
}

void OptionsHolder::setTextures(bool textures)
{
    this->textures = textures;
}

bool OptionsHolder::getEclairage()
{
    return eclairage;
}

void OptionsHolder::setEclairage(bool eclairage)
{
    this->eclairage = eclairage;
}

GLenum OptionsHolder::getMag()
{
    return mag;
}

void OptionsHolder::setMag(GLenum mag)
{
    this->mag = mag;
}

GLenum OptionsHolder::getMin()
{
    return min;
}

void OptionsHolder::setMin(GLenum min)
{
    this->min = min;
}
