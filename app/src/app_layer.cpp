// Copyright (c) 2025 Sylar129. All rights reserved

#include "app_layer.h"

#include "core/application.h"
#include "core/renderer/shader.h"
#include "glad/gl.h"

namespace prototype {

AppLayer::AppLayer() {}

AppLayer::~AppLayer() {}

void AppLayer::OnAttach() {
  // Create shaders
  shader_.Compile("shaders/vertex.glsl", "shaders/fragment.glsl");

  // Create geometry
  glCreateVertexArrays(1, &vertex_array_);
  glCreateBuffers(1, &vertex_buffer_);

  struct Vertex {
    glm::vec2 position;
    glm::vec2 tex_coord;
  };

  Vertex vertices[] = {
      {{-1.0f, -1.0f}, {0.0f, 0.0f}},  // Bottom-left
      {{3.0f, -1.0f}, {2.0f, 0.0f}},   // Bottom-right
      {{-1.0f, 3.0f}, {0.0f, 2.0f}}    // Top-left
  };

  glNamedBufferData(vertex_buffer_, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Bind the VBO to VAO at binding index 0
  glVertexArrayVertexBuffer(vertex_array_, 0, vertex_buffer_, 0,
                            sizeof(Vertex));

  // Enable attributes
  glEnableVertexArrayAttrib(vertex_array_, 0);  // position
  glEnableVertexArrayAttrib(vertex_array_, 1);  // uv

  // Format: location, size, type, normalized, relative offset
  glVertexArrayAttribFormat(vertex_array_, 0, 2, GL_FLOAT, GL_FALSE,
                            static_cast<GLuint>(offsetof(Vertex, position)));
  glVertexArrayAttribFormat(vertex_array_, 1, 2, GL_FLOAT, GL_FALSE,
                            static_cast<GLuint>(offsetof(Vertex, tex_coord)));

  // Link attribute locations to binding index 0
  glVertexArrayAttribBinding(vertex_array_, 0, 0);
  glVertexArrayAttribBinding(vertex_array_, 1, 0);
}

void AppLayer::OnDetach() {
  glDeleteVertexArrays(1, &vertex_array_);
  glDeleteBuffers(1, &vertex_buffer_);

  shader_.Delete();
}

void AppLayer::OnEvent(Event& event) {}

void AppLayer::OnUpdate(float ts) {}

void AppLayer::OnRender() {
  shader_.Use();

  // Uniforms
  shader_.SetFloat("iTime", core::Application::GetTime());

  glm::vec2 framebuffer_size = core::Application::Get().GetFramebufferSize();
  shader_.SetVec2("iResolution", framebuffer_size);

  glViewport(0, 0, static_cast<GLsizei>(framebuffer_size.x),
             static_cast<GLsizei>(framebuffer_size.y));

  // Render
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindVertexArray(vertex_array_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
}  // namespace prototype
