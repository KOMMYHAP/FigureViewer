#include "cubeEngine.h"

#include <QVector3D>

struct VectorData
{
    QVector3D position;
    QVector3D color;
};

CubeEngine::CubeEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
    , nVerteces(24)
    , nIndeces(34)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    initGeometry();
}

CubeEngine::~CubeEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void CubeEngine::initGeometry() /* override */
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    QVector3D const v[] = {
        QVector3D(-1.0f, -1.0f,  1.0f), // v0
        QVector3D( 1.0f, -1.0f,  1.0f), // v1
        QVector3D(-1.0f,  1.0f,  1.0f), // v2
        QVector3D( 1.0f,  1.0f,  1.0f), // v3
        QVector3D( 1.0f, -1.0f, -1.0f), // v4
        QVector3D(-1.0f, -1.0f, -1.0f), // v5
        QVector3D( 1.0f,  1.0f, -1.0f), // v6
        QVector3D(-1.0f,  1.0f, -1.0f)  // v7
    };
    QVector3D const c[] = {
        {0.96f, 0.54f, 0.54f},
        {0.76f, 0.54f, 0.96f},
        {0.54f, 0.61f, 0.96f},
        {0.54f, 0.84f, 0.96f},
        {0.89f, 0.64f, 0.50f},
        {0.92f, 0.96f, 0.54f}
    };

    VectorData vertices[] = {
        // Vertex data for face 0
        {v[0], c[0]}, // v0
        {v[1], c[0]}, // v1
        {v[2], c[0]}, // v2
        {v[3], c[0]}, // v3

        // Vertex data for face 1
        {v[1], c[1]}, // v4
        {v[4], c[1]}, // v5
        {v[3], c[1]}, // v6
        {v[6], c[1]}, // v7

        // Vertex data for face 2
        {v[4], c[2]}, // v8
        {v[5], c[2]}, // v9
        {v[6], c[2]}, // v10
        {v[7], c[2]}, // v11

        // Vertex data for face 3
        {v[5], c[3]}, // v12
        {v[0], c[3]}, // v13
        {v[7], c[3]}, // v14
        {v[2], c[3]}, // v15

        // Vertex data for face 4
        {v[5], c[4]}, // v16
        {v[4], c[4]}, // v17
        {v[0], c[4]}, // v18
        {v[1], c[4]}, // v19

        // Vertex data for face 5
        {v[2], c[5]}, // v20
        {v[3], c[5]}, // v21
        {v[7], c[5]}, // v22
        {v[6], c[5]}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3, 3,
         4,  4,  5,  6,  7,  7,
         8,  8,  9, 10, 11, 11, 
        12, 12, 13, 14, 15, 15,
        16, 16, 17, 18, 19, 19,
        20, 20, 21, 22, 23
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nVerteces * sizeof(VectorData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nIndeces * sizeof(GLushort));
}

void CubeEngine::drawGeometry(QOpenGLShaderProgram *program) /*	override */
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