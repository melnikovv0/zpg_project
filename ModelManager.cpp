#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "ModelManager.h"
#include "myTriangle.h" 
#include "tree.h"
#include "sphere.h"
#include "bushes.h" 
#include "plain.h"

#include <vector>
#include <iostream>

void ModelManager::loadModels() {
  
    const float* tri_begin = myTriangle;
    const float* tri_end = tri_begin + sizeof(myTriangle) / sizeof(float);
    std::vector<float> triangleVertices(tri_begin, tri_end);
    m_Models["triangle"] = std::make_unique<Model>(triangleVertices, 6);

    const float* tree_begin = tree;
    const float* tree_end = tree_begin + sizeof(tree) / sizeof(float);
    std::vector<float> treeVertices(tree_begin, tree_end);
    m_Models["tree"] = std::make_unique<Model>(treeVertices, 6);

    const float* sphere_begin = sphere;
    const float* sphere_end = sphere_begin + sizeof(sphere) / sizeof(float);
    std::vector<float> sphereVertices(sphere_begin, sphere_end);
    m_Models["sphere"] = std::make_unique<Model>(sphereVertices, 6);

    const float* bush_begin = bushes;
    const float* bush_end = bush_begin + sizeof(bushes) / sizeof(float);
    std::vector<float> bushVertices(bush_begin, bush_end);
    m_Models["bush"] = std::make_unique<Model>(bushVertices, 6);

    const float* plain_begin = plain;
    const float* plain_end = plain_begin + sizeof(plain) / sizeof(float);
    std::vector<float> plainVertices(plain_begin, plain_end);
    m_Models["plain"] = std::make_unique<Model>(plainVertices, 8);

    loadModelFromObj("assets/formula1.obj", "formula1");
    loadModelFromObj("assets/shrek.obj", "shrek");
    loadModelFromObj("assets/fiona.obj", "fiona");
    loadModelFromObj("assets/toiled.obj", "toiled");

}

Model* ModelManager::getModel(const std::string& name) {
    auto it = m_Models.find(name);

    if (it != m_Models.end()) {
        return it->second.get();
    }

    throw std::runtime_error("ModelManager Error: Model not found: " + name);
}

void ModelManager::loadModelFromObj(const std::string& filepath, const std::string& modelName) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
        throw std::runtime_error("Failed to load model: " + filepath + " | " + warn + err);
    }

    std::vector<float> vertexData;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertexData.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertexData.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertexData.push_back(attrib.vertices[3 * index.vertex_index + 2]);
            // Normals
            if (index.normal_index >= 0) {
                vertexData.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertexData.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertexData.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertexData.push_back(0.0f); vertexData.push_back(1.0f); vertexData.push_back(0.0f);
            }
            // UVs
            if (index.texcoord_index >= 0) {
                vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertexData.push_back(0.0f); vertexData.push_back(0.0f);
            }
        }
    }

    m_Models[modelName] = std::make_unique<Model>(vertexData, 8);
    std::cout << "Loaded model '" << modelName << "' from " << filepath << std::endl;
}