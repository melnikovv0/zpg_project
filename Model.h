#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices);
    ~Model();

    void draw() const;

private:
    GLuint vao, vbo;
    GLsizei vertexCount;
};

#endif
