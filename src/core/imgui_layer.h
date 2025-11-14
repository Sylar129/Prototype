// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

struct GLFWwindow;

namespace prototype {

class ImguiLayer {
 public:
  ~ImguiLayer();
  void Init(GLFWwindow* window);
  void Clean();
  void OnRenderBegin();
  void OnRender();
  void OnRenderEnd();
};

}  // namespace prototype
