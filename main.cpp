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
#include "ui_untitled.h"
#include <qapplication.h>
#include <qframe.h>
#include <QBoxLayout>
#include <QColorDialog>
#include <time.h>

#define GLUT_DISABLE_ATEXIT_HACK
#ifdef Q_OS_WIN32
#include "GL/glut.h"
#endif
#ifdef Q_OS_MAC
#include "GLUT/glut.h"
#endif

int main(int argc, char** argv)
{
    srand(time(NULL));

    //initie QT et glut
    QApplication application(argc,argv);
    QMainWindow* mainWindow = new QMainWindow;

    glutInit(&argc, argv);

    Ui_MainWindow form1;
    form1.setupUi(mainWindow);


    //cree le layout et le viewer
    Viewer *v = new Viewer(&form1);
    QLayout *layout = new QHBoxLayout;
    layout->addWidget(v);
    form1.frame->setLayout(layout);

    //connection des boutons
    mainWindow->connect(form1.playButton,SIGNAL(clicked()),v,SLOT(playHandler()));
    mainWindow->connect(form1.stopButton,SIGNAL(clicked()),v,SLOT(stopHandler()));
    mainWindow->connect(form1.speedSlider,SIGNAL(sliderMoved(int)),v,SLOT(speedHandler(int)));

    //creation des menus
    QAction option1("Textures", mainWindow);
    option1.setCheckable(true);
    option1.setChecked(true);

    QAction option2("Eclairage", mainWindow);
    option2.setCheckable(true);
    option2.setChecked(true);

    QAction optionS("Flat shading", mainWindow);
    optionS.setCheckable(true);
    optionS.setChecked(false);

    QAction optionA("Axes", mainWindow);
    optionA.setCheckable(true);
    optionA.setChecked(true);

    QAction optionC("Suivi camera", mainWindow);
    optionC.setCheckable(true);
    optionC.setChecked(false);

    QMenu affichage("Affichage", mainWindow);
    affichage.addAction(&option1);
    affichage.addAction(&option2);
    affichage.addAction(&optionS);
    affichage.addAction(&optionA);
    affichage.addAction(&optionC);

    QMenu filtrage("Filtrage", mainWindow);

    QMenu option3("Mag filter", &filtrage);
    QMenu option6("Min filter", &filtrage);

    QActionGroup agMag(mainWindow);
    QAction option4("Nearest", &agMag);
    option4.setCheckable(true);
    option4.setChecked(true);
    QAction option5("Linear", &agMag);
    option5.setCheckable(true);

    option3.addAction(&option4);
    option3.addAction(&option5);

    QActionGroup agMin(mainWindow);
    QAction option7("Nearest", &agMin);
    option7.setCheckable(true);
    option7.setChecked(true);
    QAction option8("Linear mipmap linear", &agMin);
    option8.setCheckable(true);


    option6.addAction(&option7);
    option6.addAction(&option8);

    filtrage.addMenu(&option3);
    filtrage.addMenu(&option6);

    mainWindow->menuBar()->addMenu(&affichage);
    mainWindow->menuBar()->addMenu(&filtrage);

    mainWindow->connect(&option1,SIGNAL(triggered(bool)),v,SLOT(optionTextures(bool)));
    mainWindow->connect(&option2,SIGNAL(triggered(bool)),v,SLOT(optionEclairage(bool)));
    mainWindow->connect(&option4,SIGNAL(triggered(bool)),v,SLOT(optionMagNearest(bool)));
    mainWindow->connect(&option5,SIGNAL(triggered(bool)),v,SLOT(optionMagLinear(bool)));
    mainWindow->connect(&option7,SIGNAL(triggered(bool)),v,SLOT(optionNearest(bool)));
    mainWindow->connect(&option8,SIGNAL(triggered(bool)),v,SLOT(optionLinearMipmapLinear(bool)));
    mainWindow->connect(&optionS,SIGNAL(triggered(bool)),v,SLOT(optionShading(bool)));
    mainWindow->connect(&optionA,SIGNAL(triggered(bool)),v,SLOT(optionAxes(bool)));
    mainWindow->connect(&optionC,SIGNAL(triggered(bool)),v,SLOT(optionCameraSuivi(bool)));

    mainWindow->show();
    application.exec();

    //delete les objets crees
    delete v;
    delete layout;
}
