#include "tetrahedronEngine.h"

#include <QVector3D>

struct VectorData
{
    QVector3D position;
    QVector3D color;
};

TetrahedronEngine::TetrahedronEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
    , nVerteces(12)
    , nIndeces(16)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    initGeometry();
}

TetrahedronEngine::~TetrahedronEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void TetrahedronEngine::initGeometry() /* override */
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    QVector3D const v[] = {
        QVector3D(-1.0f, -1.0f,  1.0f), // v0
        QVector3D( 1.0f,  1.0f,  1.0f), // v1
        QVector3D( 1.0f, -1.0f, -1.0f), // v2
        QVector3D(-1.0f,  1.0f, -1.0f), // v3
    };
    QVector3D const c[] = {
        {0.96f, 0.54f, 0.54f},
        {0.76f, 0.54f, 0.96f},
        {0.54f, 0.61f, 0.96f},
        {0.54f, 0.84f, 0.96f}
    };

    VectorData vertices[] = {
        // Vertex data for face 0
        {v[3], c[0]}, // v0
        {v[2], c[0]}, // v1
        {v[0], c[0]}, // v2

        // Vertex data for face 1
        {v[2], c[1]}, // v3
        {v[1], c[1]}, // v4
        {v[0], c[1]}, // v5

        // Vertex data for face 2
        {v[2], c[2]}, // v6
        {v[3], c[2]}, // v7
        {v[1], c[2]}, // v8

        // Vertex data for face 3
        {v[3], c[3]}, // v9
        {v[0], c[3]}, // v10
        {v[1], c[3]}, // v11
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
        0,  1,  2,  2,
        3,  4,  5,  5,
        6,  7,  8,  8,
        9, 10, 11
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nVerteces * sizeof(VectorData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nIndeces * sizeof(GLushort));
}

void TetrahedronEngine::drawGeometry(QOpenGLShaderProgram *program) /* override */
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VectorData));

    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VectorData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, nIndeces, GL_UNSIGNED_SHORT, 0);
}