#ifndef TETRAHEDRON_ENGINE
#define TETRAHEDRON_ENGINE

#include "geometryengine.h"

class TetrahedronEngine : public GeometryEngine
{
public:
    TetrahedronEngine();
    ~TetrahedronEngine() override;

    virtual void initGeometry() override;
    virtual void drawGeometry(QOpenGLShaderProgram *) override;

private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    const uint nVerteces;
    const uint nIndeces;
};

#endif