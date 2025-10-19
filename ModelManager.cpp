#include "ModelManager.h"


#include "myTriangle.h" 
#include "tree.h"
#include "sphere.h"
#include "bushes.h" 
#include "plain.h"

#include <vector>

void ModelManager::loadModels() {

    const float* tri_begin = myTriangle;
    const float* tri_end = tri_begin + sizeof(myTriangle) / sizeof(float);
    std::vector<float> triangleVertices(tri_begin, tri_end);

    m_Models["triangle"] = std::make_unique<Model>(triangleVertices);


    const float* tree_begin = tree;
    const float* tree_end = tree_begin + sizeof(tree) / sizeof(float);
    std::vector<float> treeVertices(tree_begin, tree_end);
    m_Models["tree"] = std::make_unique<Model>(treeVertices);

    const float* sphere_begin = sphere;
    const float* sphere_end = sphere_begin + sizeof(sphere) / sizeof(float);
    std::vector<float> sphereVertices(sphere_begin, sphere_end);
    m_Models["sphere"] = std::make_unique<Model>(sphereVertices);

    const float* bush_begin = bushes;
    const float* bush_end = bush_begin + sizeof(bushes) / sizeof(float);
    std::vector<float> bushVertices(bush_begin, bush_end);
    m_Models["bush"] = std::make_unique<Model>(bushVertices);

    const float* plain_begin = plain;
    const float* plain_end = plain_begin + sizeof(plain) / sizeof(float);
    std::vector<float> plainVertices(plain_begin, plain_end);
    m_Models["plain"] = std::make_unique<Model>(plainVertices);





    
}

Model* ModelManager::getModel(const std::string& name) {
    auto it = m_Models.find(name);

    if (it != m_Models.end()) {
        return it->second.get();
    }

    throw std::runtime_error("ModelManager Error: Model not found: " + name);
}