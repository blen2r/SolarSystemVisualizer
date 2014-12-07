#ifndef SPLINE_H
#define SPLINE_H

#include "CGLA/Vec3f.h"
using CGLA::Vec3f;

#include "shape.h"

class Spline : public Shape
{
    public:
        Spline(Node* parent);
        void draw();
        void animate();
        void addPoint(GLfloat x, GLfloat y, GLfloat z);
        void setDrawWithNames(bool drawWithNames);
        void movePoint(int point, GLfloat x, GLfloat y, GLfloat z);
        int getNbrSplines();
        void setPoints(int spline, Vec3f *point1, Vec3f *point2, Vec3f *point3, Vec3f *point4);

    private:
        bool drawWithNames;

        vector<GLfloat> points; //push_back pt1_x, push_back pt1_y, push_back pt1_z
        vector<GLfloat>::iterator first;
        vector<GLfloat>::iterator last;
};

#endif // SPLINE_H
