QT       += core gui widgets

TARGET = viewer
TEMPLATE = app

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp \
    widgetSettings.cpp \
    widgetViewer.cpp \
    cubeEngine.cpp \
    tetrahedronEngine.cpp

HEADERS += \
    mainwidget.h \
    widgetSettings.h \
    widgetViewer.h \
    geometryengine.h \
    cubeEngine.h \
    tetrahedronEngine.h

RESOURCES += \
    shaders.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target