#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
  
    explicit Model(const std::vector<float>& vertices);
    ~Model();

    void draw() const;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei vertexCount = 0;
};
