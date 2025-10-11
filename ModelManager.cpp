#include "ModelManager.h"


#include "myTriangle.h" // Предполагаем, что вы создали такой файл
#include "tree.h"
#include "sphere.h"


#include <vector>

void ModelManager::loadModels() {
    // --- ЗАДАЧА 5: Создаем модель треугольника ---
    // 1. Конвертируем C-массив 'myTriangle' из myTriange.h в std::vector
    const float* tri_begin = myTriangle;
    const float* tri_end = tri_begin + sizeof(myTriangle) / sizeof(float);
    std::vector<float> triangleVertices(tri_begin, tri_end);

    // 2. Создаем модель и сохраняем её под именем "triangle"
    m_Models["triangle"] = std::make_unique<Model>(triangleVertices);


    // --- ДОБАВЛЕНО: Модель дерева ---
    const float* tree_begin = tree;
    const float* tree_end = tree_begin + sizeof(tree) / sizeof(float);
    std::vector<float> treeVertices(tree_begin, tree_end);
    m_Models["tree"] = std::make_unique<Model>(treeVertices);

    // Для задачи 6 и 7 вы будете так же подключать sphere.h, tree.h и т.д.
    // 
    // // --- ДОБАВЛЕНО: Модель сферы ---
    const float* sphere_begin = sphere;
    const float* sphere_end = sphere_begin + sizeof(sphere) / sizeof(float);
    std::vector<float> sphereVertices(sphere_begin, sphere_end);
    m_Models["sphere"] = std::make_unique<Model>(sphereVertices);
    // и добавлять их в m_Models под своими именами.
}

Model* ModelManager::getModel(const std::string& name) {
    // Ищем модель в нашем хранилище по имени
    auto it = m_Models.find(name);

    // Проверяем, нашли ли мы её
    if (it != m_Models.end()) {
        // Если да, возвращаем обычный указатель на модель.
        // Владение при этом остается у unique_ptr в m_Models.
        return it->second.get();
    }

    // Если модель не найдена, сообщаем о критической ошибке
    throw std::runtime_error("ModelManager Error: Model not found: " + name);
}