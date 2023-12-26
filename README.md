OpenEngine 游戏引擎
OpenEngine 是一个多功能强大的游戏引擎，旨在提供一套全面的游戏开发工具。它包含了从物理模拟到渲染、输入处理、用户界面管理等广泛的功能。

特性
物理模拟: 支持碰撞检测（AABB, ColliderComponent, Contact, PhysicSystem）、刚体动力学（RigidBody, RigidBodyComponent）以及各种物理阶段（BoardPhase, IntegratePhase, ResolutionPhase, NarrowPhase）。

渲染系统: （Renderer, MeshRendererComponent, MeshRendererSystem, GeometryComponent），支持不同的着色器（Shader）、纹理（Texture）和材料（Material）。

输入处理: 输入系统（Input, InputComponent, InputSystem, EKey, EMouseButton），管理键盘和鼠标交互。

用户界面: 创建交互式和响应式用户界面的UI组件（UI, UIComponent, UISystem）。

实体-组件-系统(ECS): 灵活的ECS架构（Entity, IComponent, ISystem），允许模块化和可扩展的游戏对象管理。

摄像机系统: 摄像机处理（CameraComponent, CameraSystem），用于动态渲染场景。

MonoBehaviour 系统: 支自定义脚本和行为（MonoBehaviourSystem, Monobehaviour）。

资产管理: （Asset, AssetDatabase, AssetImporter, MaterialImporter, ModelImporter, ShaderImporter, TextureImporter），用于各种游戏资产。

实用工具: （Math, Logger, IniFile, GUID, ServiceLocator）。

外部库集成: assimp, eigen, boost, openGL, GLAD, GLFW, ImGui等外部库

项目结构
