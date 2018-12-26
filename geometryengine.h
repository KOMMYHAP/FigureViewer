#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
	virtual ~GeometryEngine() = default;

	virtual void initGeometry() = 0;
    virtual void drawGeometry(QOpenGLShaderProgram *) = 0;
};

#endif // GEOMETRYENGINE_H
