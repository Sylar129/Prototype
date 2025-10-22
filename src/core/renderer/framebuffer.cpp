// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/framebuffer.h"

#include "core/log.h"
#include "glad/gl.h"
#include "stb/stb_image.h"

namespace prototype::renderer {

void Framebuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, handle);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

Framebuffer CreateFrameBuffer() {
  constexpr int kWidth = 1920;
  constexpr int kHeight = 1080;
  Framebuffer framebuffer;
  glGenFramebuffers(1, &framebuffer.handle);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.handle);

  glGenTextures(1, &framebuffer.color_attachment);
  glBindTexture(GL_TEXTURE_2D, framebuffer.color_attachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, kWidth, kHeight, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         framebuffer.color_attachment, 0);

  glGenRenderbuffers(1, &framebuffer.render_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, framebuffer.render_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, kWidth, kHeight);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, framebuffer.render_buffer);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    CORE_LOG_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return framebuffer;
}

}  // namespace prototype::renderer
