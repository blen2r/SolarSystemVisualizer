#include "spline.h"

#include <iostream>
using namespace std;

#define SIZE_BOUND 1.0f

Spline::Spline(Node* parent) : Shape(parent)
{
    drawWithNames = false;
}

void Spline::draw()
{
    glEnable(GL_MAP1_VERTEX_3);


    //affichage points de controle
    if(drawWithNames)
    {
        glColor3f(1.0, 1.0, 1.0);

        glPointSize(5.0);
        glColor3f(1.0, 1.0, 1.0);

        for (int i = 0; i < points.size(); i+=3)
        {
            glPushName(i/3);

            //bounding box pour que ca soit plus facile a selectionner
            glBegin(GL_QUADS);
                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);

                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);

                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);

                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);

                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f(-SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);

                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], SIZE_BOUND+points[i+2]);
                glVertex3f( SIZE_BOUND+points[i], -SIZE_BOUND+points[i+1], -SIZE_BOUND+points[i+2]);
            glEnd();
            glPopName();
        }

    }else
    {
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(3.0);

        int nbrSplines = 0;

        if(points.size() == 12)
            nbrSplines = 1;
        else if(points.size() > 12) //on a plus qu'un spline, doivent etre complets
            nbrSplines = (points.size()-12)/(3*3) + 1;

        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);

        for(int spline = 0; spline < nbrSplines; spline++)
        {

            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &points[spline*3*3]); //3*3 car 4 points par spline (mais connectes au centre donc un point commun), divise par 3 coords

            glBegin(GL_LINE_STRIP);
                for (int i = 0; i <= 100; i++)
                {
                    glEvalCoord1f((GLfloat) i / 100.0f);
                }
            glEnd();
         }

        glPointSize(5.0);
        glColor3f(1.0, 1.0, 1.0);

        //affiche les points de controle
        glBegin(GL_POINTS);
            for (int i = 0; i < points.size(); i+=3)
            {
                glVertex3f(points.at(i), points.at(i +1), points.at(i + 2));
            }
        glEnd();
        glPointSize(1.0);
        glPopAttrib();

    }

}

void Spline::animate()
{
}

void Spline::addPoint(GLfloat x, GLfloat y, GLfloat z)
{
     points.push_back(x);
     points.push_back(y);
     points.push_back(z);
}

void Spline::setDrawWithNames(bool drawWithNames)
{
    this->drawWithNames = drawWithNames;
}

void Spline::movePoint(int point, GLfloat x, GLfloat y, GLfloat z)
{
    first = points.begin() + point*3;
    last = first + 3;

    points.erase(first, last);

    first = points.begin() + point*3;
    points.insert(first, z);
    points.insert(first, y);
    points.insert(first, x);

}

int Spline::getNbrSplines()
{
    int nbrSplines = 0;

    if(points.size() == 12)
        nbrSplines = 1;
    else if(points.size() > 12) //on a plus qu'un spline, doivent etre complets
        nbrSplines = (points.size()-12)/(3*3) + 1;

    return nbrSplines;
}

void Spline::setPoints(int spline, Vec3f *point1, Vec3f *point2, Vec3f *point3, Vec3f *point4)
{
    point1->set(points.at(spline*3*3), points.at(spline*3*3+1), points.at(spline*3*3+2));
    point2->set(points.at(spline*3*3+3), points.at(spline*3*3+4), points.at(spline*3*3+5));
    point3->set(points.at(spline*3*3+6), points.at(spline*3*3+7), points.at(spline*3*3+8));
    point4->set(points.at(spline*3*3+9), points.at(spline*3*3+10), points.at(spline*3*3+11));
}
