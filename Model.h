#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
    // vertices: interleaved xyz nx ny nz (6 float на вершину)
    explicit Model(const std::vector<float>& vertices);
    ~Model();

    void draw() const;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei vertexCount = 0;
};
