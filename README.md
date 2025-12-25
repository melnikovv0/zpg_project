# OpenGL 3D Graphics Engine

A modern 3D graphics application built with **C++** and **OpenGL 3.3**. This project demonstrates core computer graphics concepts including hierarchical scene graphs, advanced lighting models, and texture mapping.
---
## 🚀 Key Features

---

* **Solar System Simulation:** Realistic hierarchical movement where the Moon orbits the Earth, and the Earth orbits the Sun using a custom transformation chain.
* **Phong Reflection Model:** Implementation of Ambient, Diffuse, and Specular lighting components in GLSL.
* **Multiple Light Sources:** Support for multiple simultaneous lights, including:
    * **Directional Light** (Sun/Moonlight)
    * **Point Lights** (Light bulbs/Fireflies with attenuation)
    * **Spotlights** (Flashlights with smooth edges)
* **Advanced Transformation System:** A composite pattern-based system for handling Translation, Rotation, and Scaling.
* **Texture Mapping:** Support for 2D textures with wrapping and filtering modes.
* **Resource Management:** Dedicated managers for Shaders, Models (.obj), Textures, and Lights.
* **Camera System:** Interactive 6-DOF camera with Keyboard and Mouse control.

---

## 🛠 Tech Stack

* **Language:** C++17
* **Graphics API:** OpenGL 3.3 (Core Profile)
* **Windowing & Input:** GLFW
* **Extension Loader:** GLEW
* **Math Library:** GLM (OpenGL Mathematics)
* **Image Loading:** stb_image

---

## 📂 Project Structure

* `ModelManager`: Handles loading and storage of 3D meshes (built-in and .obj files).
* `ShaderManager`: Manages GLSL shader compilation and uniform updates.
* `TextureManager`: Loads and binds 2D textures.
* `LightManager`: Manages light sources and synchronizes them with shaders using the Observer pattern.
* `SceneBuilders`: Contains predefined scenes (e.g., Solar System, Forest Scene).

---

## 🎮 Controls

* **W / A / S / D**: Move camera.
* **Mouse**: Look around (Yaw/Pitch).
* **Scroll**: Zoom in/out (Field of View).

### 👨‍💻 Author
**Evgenii Melnikov** *VŠB-TUO, FEI*
