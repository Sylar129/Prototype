// Copyright (c) 2025 Sylar129. All rights reserved

#include "core/renderer/framebuffer.h"

#include "core/log.h"
#include "glad/gl.h"

namespace prototype {

Framebuffer::Framebuffer(int w, int h) : width(w), height(h) {
  glGenFramebuffers(1, &handle);
  glBindFramebuffer(GL_FRAMEBUFFER, handle);

  glGenTextures(1, &color_attachment);
  glBindTexture(GL_TEXTURE_2D, color_attachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         color_attachment, 0);

  glGenRenderbuffers(1, &render_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    CORE_LOG_ERROR("ERROR::FRAMEBUFFER::Framebuffer is not complete!");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BeginRecording() {
  glBindFramebuffer(GL_FRAMEBUFFER, handle);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void Framebuffer::EndRecording() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

}  // namespace prototype
