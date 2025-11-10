#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept> 

#include "Model.h"

class ModelManager {
public:
    
    void loadModels();

    Model* getModel(const std::string& name);

private:   

    void loadModelFromObj(const std::string& filepath, const std::string& modelName);

    std::map<std::string, std::unique_ptr<Model>> m_Models;
};