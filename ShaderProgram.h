#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "IObserver.h"
#include "Light.h"

class Camera;
class LightManager;


class ShaderProgram : public IObserver {
public:
    ShaderProgram(const std::string& vertexFilepath, const std::string& fragmentFilepath);
    ~ShaderProgram();

    void use() const;

    void update(ISubject* subject) override;

    void setUniform(const char* name, int v) const;
    void setUniform(const char* name, float v) const;
    void setUniform(const char* name, const glm::mat4& m) const;
    void setUniform(const char* name, const glm::vec3& v) const;


private:
    GLuint programId = 0;
    void link(const Shader& vs, const Shader& fs);

};
