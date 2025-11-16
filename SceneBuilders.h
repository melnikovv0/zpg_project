
class Scene;
class ModelManager;
class ShaderManager;
class Camera;
class LightManager;
class TextureManager;

namespace SceneBuilders {

    void buildScene1(Scene& scene, ModelManager& models, ShaderManager& shaders, Camera& camera, LightManager& lightManager);
    void buildScene2(Scene& scene, ModelManager& models, ShaderManager& shaders, Camera& camera, LightManager& lightManager);
    void buildScene3(Scene& scene, ModelManager& models, ShaderManager& shaders, TextureManager& textures, Camera& camera, LightManager& lightManager);

}