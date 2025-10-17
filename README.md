# Prototype

> 🚀 A lightweight C++ software framework prototype inspired by [TheCherno/Architecture](https://github.com/TheCherno/Architecture),  
> designed for **fast startup**, **modular experimentation**, and **system architecture prototyping**.

---

## 🧩 项目简介 | Overview

**Prototype** 是一个基于 **C++17/20** 的快速原型框架，旨在帮助开发者：
- 快速搭建一个**可运行的应用框架**（无需重复造轮子）
- 测试 **模块化架构 / 组件系统 / 渲染管线 / 应用层设计**
- 作为 **游戏引擎、图形框架或工具应用的起点**

该项目的灵感来自于 [TheCherno 的 Architecture 项目](https://github.com/TheCherno/Architecture)，并在此基础上进行了简化和结构优化。

---

## 🏗️ 项目目标 | Goals

- 🧱 提供一个干净、模块化的项目结构  
- 🧭 支持 **快速原型验证（Prototype）**：能迅速添加、测试系统或功能  
- 🎮 适合作为游戏引擎 / 工具软件 / 图形项目的启动模板  
- 🔌 便于集成第三方库（GLFW、Glad、spdlog、ImGui、glm 等）  
- 🧩 结构清晰，可轻松扩展应用层和核心层逻辑

---

## 🧱 项目结构 | Project Structure

```
Prototype/
├── app/                  # 应用层（入口与高层逻辑）
│   ├── main.cpp
│   └── Application.cpp
├── core/                 # 核心框架（基础设施 / 系统模块）
│   ├── Core.h
│   ├── Log.h / .cpp
│   ├── Window.h / .cpp
│   └── EntryPoint.h
├── vendor/               # 第三方库（GLFW / spdlog / glm 等）
├── CMakeLists.txt        # 构建脚本
├── .clang-format         # 代码格式规范
└── LICENSE               # 开源许可证 (Unlicense)
```

## 🔍 模块化设计 | Modular Philosophy

| 模块 | 功能 | 状态 |
|------|------|------|
| **Core** | 框架核心、生命周期、日志系统、入口管理 | ✅ |
| **Window** | 窗口与上下文管理（GLFW） | ⚙️ 开发中 |
| **Renderer** | 基础渲染接口 / 封装 | 🧩 规划中 |
| **Event System** | 事件与输入分发机制 | 🧩 规划中 |
| **Application Layer** | 应用主循环与层级系统 | ⚙️ 实现中 |
| **ImGui Integration** | 可选 GUI 调试层 | 🚧 计划中 |

---

## 🧠 开发理念 | Design Philosophy

- **最小可行架构（Minimal Viable Architecture）**  
  用最少的代码搭建清晰的层次结构。
- **解耦与扩展性**  
  每个模块都可以被独立替换或扩展。
- **易于理解与修改**  
  适合个人实验、引擎学习或教学示例。
- **Inspired by TheCherno**  
  复刻并改进他的视频与项目中提到的架构理念。

---

## 🚀 未来计划 | Roadmap

- [ ] 完善 Window 系统与渲染循环  
- [ ] 增加 Layer / Event 系统  
- [ ] 集成 ImGui  
- [ ] 添加 ECS（实体组件系统）实验模块  
- [ ] 增加单元测试与示例程序  
- [ ] 编写更详细的文档与教程  

---

## 📜 许可证 | License

本项目基于 [The Unlicense](https://unlicense.org/) 发布。  
属于公共领域软件，任何人可自由使用、修改、发布、分发，无需许可或署名。

---

## 🤝 致谢 | Acknowledgements

- [TheCherno](https://github.com/TheCherno) — 原始架构与理念启发  
- [GLFW](https://www.glfw.org/) / [Glad](https://glad.dav1d.de/)  
- [spdlog](https://github.com/gabime/spdlog)  
- [glm](https://github.com/g-truc/glm)  
