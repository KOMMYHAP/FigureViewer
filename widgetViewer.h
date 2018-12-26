#ifndef VIEWER_H
#define VIEWER_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>

class GeometryEngine;

class WidgetViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit WidgetViewer(QWidget *parent = 0);
    ~WidgetViewer();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();

    QSize sizeHint() const override;

public slots:
	void setGeometryEngine(QString const &);
	void setScale(qreal);
    void enableSpeedAttenuation(bool);

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *m_pEngine;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    QQuaternion rotation;

    qreal m_angularSpeed;
    qreal m_scale;
    bool m_enableSpeedAttenuation;
};

#endif