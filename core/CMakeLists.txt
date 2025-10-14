#
# core
#

set(SOURCES
    vendor/stb/stb_image.h
    vendor/stb/stb_image.cpp
    src/core/application.h
    src/core/application.cpp
    src/core/window.h
    src/core/window.cpp
    src/core/layer.h
    src/core/log.h
    src/core/log.cpp
    src/core/imgui_layer.h
    src/core/imgui_layer.cpp
    src/core/renderer/renderer.h
    src/core/renderer/renderer.cpp
    src/core/renderer/shader.h
    src/core/renderer/shader.cpp
    src/core/renderer/utils.h
    src/core/renderer/utils.cpp
)

add_library(core STATIC)

target_sources(core PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(core spdlog)
target_link_libraries(core glfw)
target_link_libraries(core glad)
target_link_libraries(core glm)
target_link_libraries(core imguilib)

target_include_directories(core PUBLIC "src" "vendor/stb")
