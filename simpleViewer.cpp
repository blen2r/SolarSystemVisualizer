/****************************************************************************

 Copyright (C) 2002-2008 Gilles Debunne. All rights reserved.

 This file is part of the QGLViewer library version 2.3.6.

 http://www.libqglviewer.com - contact@libqglviewer.com

 This file may be used under the terms of the GNU General Public License
 versions 2.0 or 3.0 as published by the Free Software Foundation and
 appearing in the LICENSE file included in the packaging of this file.
 In addition, as a special exception, Gilles Debunne gives you certain
 additional rights, described in the file GPL_EXCEPTION in this package.

 libQGLViewer uses dual licensing. Commercial/proprietary software must
 purchase a libQGLViewer Commercial License.

 This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************************/

#include "simpleViewer.h"
#include "optionsholder.h"

#include <qgl.h>
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef Q_OS_WIN32
#include "GL/glut.h"
#endif
#ifdef Q_OS_MAC
#include "GLUT/glut.h"
#endif

#include "transformgroup.h"
#include "shape.h"
#include "sphere.h"
#include "ring.h"
#include "barre.h"
#include "texture.h"
#include "light.h"
#include "vaisseau.h"
#include "firetrail.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <qevent.h>

#include "CGLA/Mat1x3f.h"
#include "CGLA/Mat1x4f.h"
#include "CGLA/Mat3x4f.h"
#include "CGLA/Mat4x4f.h"
#include "CGLA/Vec3f.h"
#include "CGLA/Vec4f.h"

using namespace CGLA;

Viewer::Viewer(Ui_MainWindow* form )
{
    this->form = form;
    selectedSplinePoint = -1;
    movingObject = false;
    suivreVaisseau = false;
}

Viewer::~Viewer()
{
    delete root; //le destructeur de Node va effacer les enfants
}

void Viewer::draw()
{

    if(suivreVaisseau && this->tgVaisseau){
        GLfloat x = this->tgVaisseau->getXTrans();
        GLfloat y = this->tgVaisseau->getYTrans();
        GLfloat z = this->tgVaisseau->getZTrans();

        gluLookAt(x-10,y-10,z+10,
                  0,0,0,
                  0,0,1);
    }


    glMatrixMode(GL_MODELVIEW);

    //pour chaque enfant de "root", on applique la transformation du transformgroup et on affiche la forme
    root->actionSequences();
}

void Viewer::drawWithNames()
{
    glMatrixMode(GL_MODELVIEW);
    spline->setDrawWithNames(true);

    //pour chaque enfant de "root", on applique la transformation du transformgroup et on affiche la forme
    root->actionSequences();
    spline->setDrawWithNames(false);
}

void Viewer::postSelection(const QPoint& point)
{
    camera()->convertClickToLine(point, orig, dir);
    bool found;
    selectedPoint = camera()->pointUnderPixel(point, found);

    if (selectedName() != -1)
    {
        movingObject = true; //demarrage du "drag'n'drop"
        selectedSplinePoint = selectedName();
    }
    else //si rien selectionne, on deselectionne l'objet precedant
    {
        movingObject = false;
        selectedSplinePoint = -1;
    }
}

void Viewer::mouseMoveEvent(QMouseEvent* e) {
    //si "drag'n'drop" en cours
    if (movingObject)
    {
        camera()->convertClickToLine(e->pos(), orig, dir);
        bool found;
        selectedPoint = camera()->pointUnderPixel(e->pos(), found);

        if(selectedSplinePoint != -1 && !suivreVaisseau)
        {
            //spline->movePoint(selectedSplinePoint, (camera()->worldCoordinatesOf(selectedPoint)).x, (camera()->worldCoordinatesOf(selectedPoint)).y, 0.0f);
            GLdouble posX, posY, posZ;

            posX = orig.x + 1000 * camera()->viewDirection().x;
            posY = orig.y + 1000 * camera()->viewDirection().y;
            posZ = orig.z + 1000 * camera()->viewDirection().z;

            spline->movePoint(selectedSplinePoint, posX, posY, posZ);

        }

        updateGL();
    }

    // Normal QGLViewer behavior.
    QGLViewer::mouseMoveEvent(e);
}

void Viewer::mouseReleaseEvent(QMouseEvent* e) {
    //si "drag'n'drop" en cours lors du relachement de la souris
    if (movingObject)
    {
        movingObject = false;
        selectedSplinePoint = -1;
    }
    QGLViewer::mouseReleaseEvent(e);
}

void Viewer::mousePressEvent(QMouseEvent*e)
{
    //CTRL+Click
    if (e->button() == Qt::LeftButton && e->modifiers() == Qt::ControlModifier)
    {
        if(!suivreVaisseau)
        {
            camera()->convertClickToLine(e->pos(), orig, dir);
            bool found;
            selectedPoint = camera()->pointUnderPixel(e->pos(), found);


            /*//adapte du code de NEHE: http://nehe.gamedev.net/article/using_gluunproject/16013/
            GLint viewport[4];
            GLdouble modelview[16];
            GLdouble projection[16];
            GLfloat winX, winY, winZ;
            GLdouble posX, posY, posZ;

            glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
            glGetDoublev( GL_PROJECTION_MATRIX, projection );
            glGetIntegerv( GL_VIEWPORT, viewport );

            winX = (float)(e->pos().x());
            winY = (float)viewport[3] - (float)(e->pos().y());
            glReadPixels( (e->pos().x()), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

            gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

            //spline->addPoint((camera()->worldCoordinatesOf(selectedPoint)).x, (camera()->worldCoordinatesOf(selectedPoint)).y, 0.0f);

            GLdouble posZ2;
            posZ2 = camera()->position().z + 800 * camera()->viewDirection().z;
            spline->addPoint(posX, posY, posZ2);
            cout<<camera()->position().z<<" "<<camera()->viewDirection().z<<" "<<posZ2<<endl;*/

            GLdouble posX, posY, posZ;

            posX = orig.x + 1000 * camera()->viewDirection().x;
            posY = orig.y + 1000 * camera()->viewDirection().y;
            posZ = orig.z + 1000 * camera()->viewDirection().z;

            spline->addPoint(posX, posY, posZ);
        }

    }

    Qt::MouseButton state = Qt::MouseButton( ((int)e->button()) | ((int)e->modifiers()) );
    QMouseEvent newEvent(e->type(), e->localPos(), state, e->buttons(), e->modifiers());
    QGLViewer::mousePressEvent(&newEvent);
}

void Viewer::init()
{

    // We want to restrict ourselves to a 2D viewer.
    camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
    setMouseBinding(Qt::LeftButton, CAMERA, TRANSLATE);
    setMouseBinding(Qt::ALT + Qt::LeftButton, CAMERA, NO_MOUSE_ACTION);
    setMouseBinding(Qt::LeftButton + Qt::MidButton, CAMERA, NO_MOUSE_ACTION);
    setMouseBinding(Qt::CTRL + Qt::LeftButton + Qt::MidButton, CAMERA, NO_MOUSE_ACTION);
    setMouseBinding(Qt::RightButton, CAMERA, LOOK_AROUND);
    setMouseBinding(Qt::SHIFT + Qt::LeftButton, SELECT);

    setSceneRadius(400);
    showEntireScene();

    setAxisIsDrawn(true);
    //setGridIsDrawn(true);
    glDisable(GL_COLOR_MATERIAL);

    // Disable shading of the objects to directly get the color specified by
    // glColor.
    //glDisable(GL_LIGHTING);

    root = new TransformGroup(NULL);

    spline = new Spline(root);
    /*spline->addPoint(-50.0f, -50.0f, 0.0f);
    spline->addPoint(25.0f, 50.0f, 0.0f);
    spline->addPoint(25.0f, -50.0f, 0.0f);
    spline->addPoint(50.0f, 50.0f, 0.0f);
    spline->addPoint(70.0f, 70.0f, 0.0f);
    spline->addPoint(80.0f, 80.0f, 0.0f);
    spline->addPoint(90.0f, 90.0f, 0.0f);*/
    root->addChild(spline);


    //creer les planetes
    // soleil
    Texture* soleilTex = new Texture(root, "assets/soleil_b.jpg", true);
    root->addChild(soleilTex);

    TransformGroup* soleil = new TransformGroup(soleilTex);
    soleil->addChild(new Sphere(soleil,25,25, soleilTex->getQuadric()));
    soleil->addChild(new Light(soleil));
    soleilTex->addChild(soleil);

    // orion
    Texture* orionTex = new Texture(root, "assets/orion_b.jpg");
    root->addChild(orionTex);

    TransformGroup* orionAnnee = new TransformGroup(orionTex); //rotation autour du soleil
    orionAnnee->setZIncrement(float(-1.0/3.0));
    orionAnnee->setName("orionAnnee");
    orionTex->addChild(orionAnnee);

    TransformGroup* orionDist = new TransformGroup(orionAnnee); //distance du soleil
    orionDist->setXTrans(110.0f);
    orionAnnee->addChild(orionDist);

    TransformGroup* orionJour = new TransformGroup(orionDist); //rotation sur son axe
    orionJour->setZIncrement(5.0f);
    orionJour->setName("orionJour");
    orionJour->addChild(new Sphere(orionJour,10,25, orionTex->getQuadric()));
    orionJour->addChild(new Barre(orionJour,15));
    orionDist->addChild(orionJour);

    //satellite
    Texture* satelliteTex = new Texture(orionJour, "assets/satellite_b.jpg");
    orionJour->addChild(satelliteTex);

    TransformGroup* satelliteOrbite = new TransformGroup(satelliteTex);
    //satelliteOrbite->setZIncrement(17.14286136627f);
    satelliteOrbite->setZIncrement(17);
    satelliteOrbite->setName("sateliteOrbite");
    satelliteTex->addChild(satelliteOrbite);

    TransformGroup* satelliteDist = new TransformGroup(satelliteOrbite);
    satelliteDist->setXTrans(60.0f);
    satelliteDist->addChild(new Sphere(satelliteDist,3,25, satelliteTex->getQuadric()));
    satelliteOrbite->addChild(satelliteDist);


    // photon
    Texture* photonTex = new Texture(root, "assets/photon_b.jpg");
    root->addChild(photonTex);

    TransformGroup* photonAnnee = new TransformGroup(photonTex);
    photonAnnee->setZIncrement(2.0f*1.0f/3.0f);
    photonAnnee->setName("photonAnnee");
    photonTex->addChild(photonAnnee);

    TransformGroup* photonDist = new TransformGroup(photonAnnee);
    photonDist->setXTrans(210.0f);
    photonAnnee->addChild(photonDist);

    TransformGroup* photonNegAnnee = new TransformGroup(photonDist); //pour que le pole pointe dans le bon sens tout le temps
    photonNegAnnee->setZIncrement(-0.5);
    photonNegAnnee->setName("photonNegAnnee");
    photonDist->addChild(photonNegAnnee);

    TransformGroup* photonInclinaison = new TransformGroup(photonNegAnnee);
    photonInclinaison->setYRot(-70.0f);
    photonNegAnnee->addChild(photonInclinaison);

    TransformGroup* photonPosAnnee = new TransformGroup(photonInclinaison); //pour que le pole pointe dans le bon sens tout le temps
    photonPosAnnee->setZIncrement(0.5);
    photonPosAnnee->setName("photonPosAnnee");
    photonInclinaison->addChild(photonPosAnnee);

    TransformGroup* photonJour = new TransformGroup(photonPosAnnee);
    photonJour->setZIncrement(6.7f);
    photonJour->setName("photonJour");
    photonJour->addChild(new Sphere(photonJour,6,25, photonTex->getQuadric()));
    photonJour->addChild(new Ring(photonJour,20, 18));
    photonJour->addChild(new Barre(photonJour,12));
    photonPosAnnee->addChild(photonJour);

    // comete
    TransformGroup* cometeScale = new TransformGroup(root);
    cometeScale->setXScale(2.0f);
    root->addChild(cometeScale);

    TransformGroup* cometeAnnee = new TransformGroup(cometeScale);
    cometeAnnee->setZIncrement(-1.0f);
    cometeAnnee->setName("cometeAnnee");
    cometeScale->addChild(cometeAnnee);

    TransformGroup* cometeDist = new TransformGroup(cometeAnnee);
    cometeDist->setXTrans(350.0f);
    // cometeDist->setYTrans(350.0f/2.0f);
    cometeAnnee->addChild(cometeDist);

    TransformGroup* cometeScaleNeg = new TransformGroup(cometeDist);
    //cometeScaleNeg->setXScale(0.5f);
    cometeScaleNeg->addChild(new Sphere(cometeScaleNeg,3,25));
    cometeDist->addChild(cometeScaleNeg);


    //vaisseau
    TransformGroup* vaisseau = new TransformGroup(root);
    TransformGroup* vaisseauPos = new TransformGroup(vaisseau);

    vaisseau->setName("vaisseau");
    vaisseauPos->setName("vaisseauPos");

    objv = new Vaisseau(vaisseauPos);
    vaisseauPos->addChild(objv);
    //vaisseau->setZIncrement(2.0f);
    vaisseau->setXTrans(75.0f);
    vaisseau->setYTrans(75.0f);
    root->addChild(vaisseau);
    vaisseau->addChild(vaisseauPos);

  //  vaisseauPos->setZIncrement(2.0f);

    this->tgVaisseau = vaisseau;

    TransformGroup* fireTrailDroit = new TransformGroup(vaisseauPos);
    fireTrailDroit->setZTrans(0.2f);
    fireTrailDroit->setXTrans(1.0f);
    fireTrailDroit->setYTrans(-2.5f);
    fireTrailDroit->setXRot(115.0f);
    fireTrailDroit->setZRot(30.0f);
    fireTrailDroit->addChild(new FireTrail(fireTrailDroit));
    vaisseauPos->addChild(fireTrailDroit);

    TransformGroup* fireTrailGauche = new TransformGroup(vaisseauPos);
    fireTrailGauche->setZRot(30.0f);


    fireTrailGauche->setXRot(115.0f);
    fireTrailGauche->setXTrans(-4.0f);
    fireTrailGauche->setYTrans(-0.8f);
    fireTrailGauche->setZTrans(0.2f);

    fireTrailGauche->addChild(new FireTrail(fireTrailGauche));
    vaisseauPos->addChild(fireTrailGauche);

    updateGL();
}

void Viewer::playHandler()
{
    if(!animationIsStarted())
    {
        objv->resetFrame();
        startAnimation();
    }
}

void Viewer::stopHandler()
{
    if(animationIsStarted())
    {
        stopAnimation();
    }
}

void Viewer::speedHandler(int i)
{
    //il faut ajuster la periode de temps entre chaque frame en millisecondes.
    setAnimationPeriod(40.0f * (1.0f - ((float)i + 1.0f)/100.0f) * 2.0f);

    //il faut arreter et repartir l'animation pour que ca fonctionne
    stopAnimation();
    startAnimation();

}

void Viewer::animate()
{
    totPoints.clear();

    for(int i = 0; i < spline->getNbrSplines(); i++)
    {
        //set points
        spline->setPoints(i, &point1, &point2, &point3, &point4);

        calcBezier(20, linepoints);
        totPoints.insert(totPoints.end(), linepoints.begin(), linepoints.end());
    }

    objv->setPointsCourbe(&totPoints);

    root->animate();
}

void Viewer::optionMagNearest(bool checked){
    if(checked)
        OptionsHolder::getInstance()->setMag(GL_NEAREST);
    updateGL();
}

void Viewer::optionMagLinear(bool checked)
{
    if(checked)
        OptionsHolder::getInstance()->setMag(GL_LINEAR);
    updateGL();
}

void Viewer::optionEclairage(bool checked)
{
    OptionsHolder::getInstance()->setEclairage(checked);

    if(checked)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    updateGL();
}

void Viewer::optionLinearMipmapLinear(bool checked)
{
    if(checked)
        OptionsHolder::getInstance()->setMin(GL_LINEAR_MIPMAP_LINEAR);
    updateGL();
}

void Viewer::optionNearest(bool checked)
{
    if(checked)
        OptionsHolder::getInstance()->setMin(GL_NEAREST);
    updateGL();
}

void Viewer::optionTextures(bool checked)
{
    OptionsHolder::getInstance()->setTextures(checked);
    updateGL();
}

void Viewer::optionShading(bool checked)
{
    if(checked)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);

    updateGL();
}

void Viewer::optionAxes(bool checked)
{
    setAxisIsDrawn(checked);

    updateGL();
}

void Viewer::optionCameraSuivi(bool checked)
{
    this->suivreVaisseau = checked;

    updateGL();
}

void Viewer::calcBezier(int segmentCount, vector<float> & points) {
    if (segmentCount < 1) {
        cout << "Invalid segment count (at least 1) " << segmentCount << endl;;
        return;
    }

    // init
    points.clear();

    // prepare reusable matrices
    // Q(t) = T * M_b * G_b

    Mat4x4f m44M_b(Vec4f(-1,  3, -3,  1),
                   Vec4f( 3, -6,  3,  0),
                   Vec4f(-3,  3,  0,  0),
                   Vec4f( 1,  0,  0,  0));

    // G_b
    Mat4x3f m43G_b(point1,
                   point2,
                   point3,
                   point4);

    float t = 0.0f;
    float step = 1.0f / (float) segmentCount;

    for (t = 0.0f; t < 1.0f; t += step) {
        Mat1x4f m14TM_b; // Product of T and M_b (intermediate result)
        Mat1x3f m13Q;    // Final Result Q = T M_b G_b

        // T
        Mat1x4f m14T(Vec4f(t*t*t, t*t, t, 1));

        mul(m14T, m44M_b, m14TM_b); // compute intermediate result
        mul(m14TM_b, m43G_b, m13Q); // compute final result

        points.push_back(m13Q[0][0]);
        points.push_back(m13Q[0][1]);
        points.push_back(m13Q[0][2]);
    }

    // add the last point
    points.push_back(point4[0]);
    points.push_back(point4[1]);
    points.push_back(point4[2]);
}
