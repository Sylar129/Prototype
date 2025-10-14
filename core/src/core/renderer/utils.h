// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glad/gl.h"

namespace prototype::renderer::utils {

const char* GLDebugSourceToString(GLenum source);
const char* GLDebugTypeToString(GLenum type);
const char* GLDebugSeverityToString(GLenum severity);

void InitOpenGLDebugMessageCallback();

}  // namespace prototype::renderer::utils
