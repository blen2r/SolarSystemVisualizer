#include "firetrail.h"

#include <math.h>
#include <iostream>
#include <time.h>

using namespace std;

// source: http://www.naturewizard.com/tutorial08.html

typedef struct
{
    float lifetime;
    float decay;
    float r,g,b;
    float rDecay, gDecay, bDecay;
    float xpos,ypos,zpos;
    float xspeed,yspeed,zspeed;
    bool active;
} PARTICLE;


const int maxparticle=100;
PARTICLE particle[maxparticle];

FireTrail::FireTrail(Node* parent)  : Shape(parent)
{
    for(int i=0;i<=maxparticle;i++)
    {
        CreateParticle(i);
        particle[i].active = false;
    }


    this->quadric = gluNewQuadric();
}

void FireTrail::draw(){

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);

    for (int i=0;i<=maxparticle;i++){
        if(particle[i].ypos<0.0)
            particle[i].lifetime=0.0;

        if((particle[i].active==true) && (particle[i].lifetime>0.0))
        {
            glColor3f(particle[i].r,particle[i].g,particle[i].b);

            glTranslatef(particle[i].xpos+2.0, particle[i].ypos+2.0, particle[i].zpos+0.0);
            gluSphere(quadric, 0.5, 25,25);
            glTranslatef(-(particle[i].xpos+2.0), -(particle[i].ypos+2.0), -(particle[i].zpos+0.0));


        }else
            CreateParticle(i);
    }

    glPopAttrib();
}

void FireTrail::animate(){
    this->EvolveParticles();
}

void FireTrail::CreateParticle(int i)
{
    particle[i].lifetime= (float)random(50)/50.0f;
    particle[i].decay=0.04;

    particle[i].r = 0.0;
    particle[i].g = 0.0;
    particle[i].b = 0.0;

    particle[i].rDecay = 2.0;
    particle[i].gDecay = 0.3;
    particle[i].bDecay = 0.10;

    particle[i].xpos= 0.0;
    particle[i].ypos= 0.0;
    particle[i].zpos= 0.0;

    float dir = 1.0f;
    if((int)(random(100))%2 == 0)
        dir = -1.0f;

    float dir2 = 1.0f;
    if((int)(random(25))%2 == 0)
        dir2 = -1.0f;

    particle[i].xspeed = dir * 0.01f + dir2 * (float)random(100) /200.0;
    particle[i].yspeed = dir * 0.01f + dir2 * (float)random(100) /200.0;
    particle[i].zspeed = 1.0 - (float)random(10) /10.0;

    particle[i].active = true;
}

void FireTrail::EvolveParticles()
{
    for(int i=0;i<=maxparticle;i++)
    {
        particle[i].lifetime-=particle[i].decay;
        particle[i].xpos+=particle[i].xspeed;
        particle[i].ypos+=particle[i].yspeed;
        particle[i].zpos+=particle[i].zspeed;

        particle[i].r = particle[i].r + particle[i].rDecay;
        particle[i].g = particle[i].g + particle[i].gDecay;
        particle[i].b = particle[i].b + particle[i].bDecay;
    }
}

float FireTrail::random(int i){
    return rand() % i;
}

