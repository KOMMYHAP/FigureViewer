#include "widgetViewer.h"

#include <QMouseEvent>
#include <math.h>

#include "cubeEngine.h"
#include "tetrahedronEngine.h"

WidgetViewer::WidgetViewer(QWidget *parent) 
	: QOpenGLWidget(parent)
	, m_pEngine(nullptr)
	, m_angularSpeed(0.0f)
	, m_scale(-5.0f)
    , m_enableSpeedAttenuation(true)
{}

WidgetViewer::~WidgetViewer()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete m_pEngine;
    doneCurrent();
}

QSize WidgetViewer::sizeHint() const
{
	return QSize(500, 500);
}

void WidgetViewer::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void WidgetViewer::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 50.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * m_angularSpeed + n * acc).normalized();

    // Increase angular speed
    m_angularSpeed += acc;
}

void WidgetViewer::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    if (m_enableSpeedAttenuation) {
        m_angularSpeed *= 0.99;

        // Stop rotation when speed goes below threshold
        if (m_angularSpeed < 0.01) {
            m_angularSpeed = 0.0;
        }
    }
    
    // Update rotation
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, m_angularSpeed) * rotation;

    // Request an update
    update();
}

void WidgetViewer::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.4f, 0.4f, 1.0f);

    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

	setGeometryEngine("Тетраэдр");

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void WidgetViewer::setGeometryEngine(QString const &name)
{
	if (m_pEngine != nullptr) 
		delete m_pEngine;

    if (name == "Куб")
        m_pEngine = new CubeEngine;
    else if (name == "Тетраэдр")
        m_pEngine = new TetrahedronEngine;
    else {
        qCritical("%s(%s): incorrect parametr!", 
            __FUNCTION__, name.toStdString().c_str());
        return;
    }

	update();
}

void WidgetViewer::setScale(qreal value)
{
	m_scale = value;
	update();
}

void WidgetViewer::enableSpeedAttenuation(bool value)
{
    m_enableSpeedAttenuation = value;
}

void WidgetViewer::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void WidgetViewer::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0
    const qreal zNear = 3.0, zFar = 80.0, fov = 45.0f;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void WidgetViewer::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, m_scale);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Draw geometry
    if (m_pEngine)
    	m_pEngine->drawGeometry(&program);
}