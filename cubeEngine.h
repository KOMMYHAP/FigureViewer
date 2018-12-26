#ifndef CUBE_ENGINE
#define CUBE_ENGINE

#include "geometryengine.h"

class CubeEngine : public GeometryEngine
{
public:
    CubeEngine();
    ~CubeEngine() override;

    virtual void initGeometry() override;
    virtual void drawGeometry(QOpenGLShaderProgram *) override;

private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    const uint nVerteces;
    const uint nIndeces;
};

#endif