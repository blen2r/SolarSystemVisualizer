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

#include <QGLViewer/qglviewer.h>
#include <string>
#include "CGLA/Vec3f.h"
using CGLA::Vec3f;
using namespace std;

#include "node.h"
#include "ui_untitled.h"
#include "spline.h"
#include "vaisseau.h"
#include "transformgroup.h"


class Viewer : public QGLViewer
{
    Q_OBJECT
protected :
    virtual void draw();
    virtual void drawWithNames();
    virtual void init();
    virtual void postSelection(const QPoint& point);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent*e);
    void calcBezier(int segmentCount, vector<float> & points);

public slots :
    void playHandler();
    void stopHandler();
    void speedHandler(int i);
    void animate();

    void optionTextures(bool checked);
    void optionEclairage(bool checked);
    void optionMagNearest(bool checked);
    void optionMagLinear(bool checked);
    void optionNearest(bool checked);
    void optionLinearMipmapLinear(bool checked);
    void optionShading(bool checked);
    void optionAxes(bool checked);
    void optionCameraSuivi(bool checked);

private:
    Node* root;
    Ui_MainWindow* form;
    bool movingObject;
    qglviewer::Vec orig, dir, selectedPoint;
    Spline* spline;
    int selectedSplinePoint;
    Vaisseau *objv;
    TransformGroup* tgVaisseau;
    bool suivreVaisseau;

    vector<float> linepoints;
    vector<float> totPoints;

    Vec3f point1;
    Vec3f point2;
    Vec3f point3;
    Vec3f point4;

public:
    Viewer(Ui_MainWindow* form );
    ~Viewer();
};

