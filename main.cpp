#include <QApplication>
#include <QSurfaceFormat>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Viewer");
    app.setApplicationVersion("0.4");

    MainWidget widget;
    widget.show();

    return app.exec();
}
