#include "SceneBuilders.h"

#include "Scene.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "LightManager.h"
#include "CompositeTransform.h"
#include "Rotation.h"
#include <glm/ext/matrix_transform.hpp>
#include <random>
#include "Translation.h"
#include "Scale.h"
#include <GLFW/glfw3.h>
void SceneBuilders::buildScene1(Scene& scene, ModelManager& models, ShaderManager& shaders, Camera& camera, LightManager& lightManager) {
    Model* triangleModel = models.getModel("triangle");
    ShaderProgram* greenShader = shaders.getShader("green");

    camera.addObserver(greenShader);

    auto& triangleObj = scene.add(triangleModel, greenShader);

    auto rotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)); 
    triangleObj.setTransform(rotation);

    scene.setUpdateCallback([rotation](float dt) {
        rotation->setAngle(rotation->getAngle() + 1.5f * dt); 
        });


}

void SceneBuilders::buildScene2(Scene& scene, ModelManager& models, ShaderManager& shaders, Camera& camera, LightManager& lightManager) {
    Model* sphereModel = models.getModel("sphere");
    ShaderProgram* constantShader = shaders.getShader("constant");
    ShaderProgram* lambertShader = shaders.getShader("lambert");
    ShaderProgram* phongShader = shaders.getShader("phong");
    ShaderProgram* blinnShader = shaders.getShader("blinn");


    lightManager.addLight(std::make_unique<Light>(
        glm::vec3(0.0f,0.0f, 0.0f),       
        glm::vec3(0.1f),                 
        glm::vec3(0.8f),                   
        glm::vec3(1.0f)                    
    ));

 
    camera.addObserver(constantShader);
    lightManager.addObserver(constantShader);

    camera.addObserver(lambertShader);
    lightManager.addObserver(lambertShader);

    camera.addObserver(phongShader);
    lightManager.addObserver(phongShader);

    camera.addObserver(blinnShader);
    lightManager.addObserver(blinnShader);

    phongShader->update(&camera);        
    phongShader->update(&lightManager);   
    blinnShader->update(&camera);         
    blinnShader->update(&lightManager);

    lambertShader->update(&camera);
    lambertShader->update(&lightManager);
    constantShader->update(&camera);
    constantShader->update(&lightManager);

    glm::vec3 object_color = glm::vec3(0.0f, 0.5f, 1.0f);

    // Phong
    auto& sphereRight = scene.add(sphereModel, phongShader);
    sphereRight.setModelMatrix(glm::scale(glm::translate(glm::mat4(1.0f), { 0.7f, 0, 0 }), { 0.4f, 0.4f, 0.4f }));
    sphereRight.addUniform("objectColor", object_color);

    // Blinn-Phong
    auto& sphereLeft = scene.add(sphereModel, blinnShader);
    sphereLeft.setModelMatrix(glm::scale(glm::translate(glm::mat4(1.0f), { -0.7f, 0, 0 }), { 0.4f, 0.4f, 0.4f }));
    sphereLeft.addUniform("objectColor", object_color);

    // Lambert
    auto& sphereUp = scene.add(sphereModel, lambertShader);
    sphereUp.setModelMatrix(glm::scale(glm::translate(glm::mat4(1.0f), { 0, 0.7f, 0 }), { 0.4f, 0.4f, 0.4f }));
    sphereUp.addUniform("objectColor", object_color);

    // Constant 
    auto& sphereDown = scene.add(sphereModel, constantShader);
    sphereDown.setModelMatrix(glm::scale(glm::translate(glm::mat4(1.0f), { 0, -0.7f, 0 }), { 0.4f, 0.4f, 0.4f }));
    sphereDown.addUniform("objectColor", object_color);
    
}

void SceneBuilders::buildScene3(Scene& scene, ModelManager& models, ShaderManager& shaders, Camera& camera, LightManager& lightManager) {

    Model* treeModel = models.getModel("tree");
    Model* bushModel = models.getModel("bush");
    Model* planeModel = models.getModel("plain");
    ShaderProgram* multiLightShader = shaders.getShader("phong_multi");

    
    auto light1 = lightManager.addLight(std::make_unique<Light>(
        glm::vec3(0, 1, 0),         
        glm::vec3(0.05f),           
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f)             
    ));
    auto light2 = lightManager.addLight(std::make_unique<Light>(
        glm::vec3(2, 1, 0),
        glm::vec3(0.10f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f)
    ));

    camera.addObserver(multiLightShader);
    lightManager.addObserver(multiLightShader);

    multiLightShader->update(&camera);
    multiLightShader->update(&lightManager);

    auto& planeObj = scene.add(planeModel, multiLightShader);
    planeObj.setModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(20.0f)));
    planeObj.addUniform("objectColor", glm::vec3(0.0f, 0.8f, 0.0f));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> posDist(-20.0, 20.0);
    std::uniform_real_distribution<> scaleDist(0.8, 1.2);
    std::uniform_real_distribution<> angleDist(0.0, 360.0);

    for (int i = 0; i < 50; ++i) {
        auto& treeObj = scene.add(treeModel, multiLightShader);

        treeObj.addUniform("objectColor", glm::vec3(0.4f, 0.2f, 0.0f));

        float x = static_cast<float>(posDist(gen));
        float z = static_cast<float>(posDist(gen));
        float scale = static_cast<float>(scaleDist(gen));
        float angle = static_cast<float>(angleDist(gen));

        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0)));
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
        treeObj.setTransform(chain);
    }

    for (int i = 0; i < 50; ++i) {
        auto& bushObj = scene.add(bushModel, multiLightShader);

        bushObj.addUniform("objectColor", glm::vec3(0.1f, 0.6f, 0.1f));

        float x = static_cast<float>(posDist(gen));
        float z = static_cast<float>(posDist(gen));
        float scale = static_cast<float>(scaleDist(gen));
        float angle = static_cast<float>(angleDist(gen));

        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0)));
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
        bushObj.setTransform(chain);
    }

    scene.setUpdateCallback([light1,light2](float dt) {
        light1->setPosition({ sin(glfwGetTime() * 0.5f) * 5.0f, 1.0f, cos(glfwGetTime() * 0.5f) * 5.0f });
        light2->setPosition({ sin(glfwGetTime() * 0.8f) * 3.0f, 1.0f, cos(glfwGetTime() * 0.3f) * 3.0f });
        });
}

