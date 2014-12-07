# The simplest application example: 20 lines of code and yet all the power !

# A Viewer class is derived from QGLViewer and its <code>draw()</code> function is overloaded to
# specify the user defined OpenGL orders that describe the scene.

# This is the first example you should try, as it explains some of the default keyboard shortcuts
# and the mouse behavior of the viewer.

# This example can be cut and pasted to start the development of a new application.

TEMPLATE = app
TARGET   = simpleViewer

# Add your .ui file here
FORMS += untitled.ui

HEADERS  = simpleViewer.h \
    transformgroup.h \
    node.h \
    shape.h \
    sphere.h \
    ring.h \
    barre.h \
    texture.h \
    light.h \
    optionsholder.h \
    glm.h \
    vaisseau.h \
    firetrail.h \
    spline.h \
    CGLA/Vec4uc.h \
    CGLA/Vec4f.h \
    CGLA/Vec3usi.h \
    CGLA/Vec3uc.h \
    CGLA/Vec3i.h \
    CGLA/Vec3Hf.h \
    CGLA/Vec3f.h \
    CGLA/Vec3d.h \
    CGLA/Vec2i.h \
    CGLA/Vec2f.h \
    CGLA/Vec1f.h \
    CGLA/UnitVector.h \
    CGLA/TableTrigonometry.h \
    CGLA/RootSolvers.h \
    CGLA/Quaternion.h \
    CGLA/Mat4x4f.h \
    CGLA/Mat3x4f.h \
    CGLA/Mat3x3f.h \
    CGLA/Mat2x3f.h \
    CGLA/Mat2x2f.h \
    CGLA/Mat1x4f.h \
    CGLA/Mat1x3f.h \
    CGLA/Map.h \
    CGLA/Filter.h \
    CGLA/ExceptionStandard.h \
    CGLA/CommonDefs.h \
    CGLA/CGLA.h \
    CGLA/BitMask.h \
    CGLA/ArithVec.h \
    CGLA/ArithSqMat.h \
    CGLA/ArithMat.h \
    CGLA/ArgExtracter.h

SOURCES  = simpleViewer.cpp main.cpp \
    transformgroup.cpp \
    node.cpp \
    shape.cpp \
    sphere.cpp \
    ring.cpp \
    barre.cpp \
    texture.cpp \
    light.cpp \
    optionsholder.cpp \
    glm.cpp \
    vaisseau.cpp \
    firetrail.cpp \
    spline.cpp \
    CGLA/Vec3i.cpp \
    CGLA/Vec3f.cpp \
    CGLA/Vec2i.cpp \
    CGLA/Vec2f.cpp \
    CGLA/TableTrigonometry.cpp \
    CGLA/Quaternion.cpp \
    CGLA/Mat4x4f.cpp \
    CGLA/Mat3x3f.cpp \
    CGLA/Mat2x2f.cpp
QT *= xml opengl

# Might have to edit this to reflect the platform dependant name.
win32: LIBS += -lglut32
macx: LIBS += -framework GLUT

#CONFIG -= debug debug_and_release
CONFIG += debug_and_release qt opengl warn_on thread rtti console embed_manifest_exe

# --------------------------------------------------------------------------------------

# The remaining of this configuration tries to automatically detect the library paths.
# In your applications, you can probably simply use (see doc/compilation.html for details) :

#INCLUDEPATH *= C:/Users/debunne/Documents/libQGLViewer-2.3.6
#LIBS *= -LC:/Users/debunne/Documents/libQGLViewer-2.3.6/QGLViewer -lQGLViewer2

# Change these paths according to your configuration.

# --------------------------------------------------------------------------------------

win32 {
  LIB_FILE = QGLViewer
  CONFIG(debug, debug|release) {
    LIB_FILE = $$join(LIB_FILE,,,d)
  }
  LIB_FILE = $$join(LIB_FILE,,,2)

  LIBS += -l$${LIB_FILE}
}

OTHER_FILES += \
    assets/soleil_b.jpg \
    assets/satellite_b.jpg \
    assets/photon_b.jpg \
    assets/orion_b.jpg \
    assets/vaisseau.obj \
    assets/vaisseau.mtl

