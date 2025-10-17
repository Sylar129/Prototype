#
# core
#

set(SOURCES
    src/core/events/application_event.h
    src/core/events/event.h
    src/core/events/key_codes.h
    src/core/events/key_event.h
    src/core/events/mouse_codes.h
    src/core/events/mouse_event.h

    src/core/renderer/camera.h
    src/core/renderer/mesh.cpp
    src/core/renderer/mesh.h
    src/core/renderer/model.cpp
    src/core/renderer/model.h
    src/core/renderer/shader.cpp
    src/core/renderer/shader.h
    src/core/renderer/texture.cpp
    src/core/renderer/texture.h
    src/core/renderer/utils.cpp
    src/core/renderer/utils.h

    src/core/application.cpp
    src/core/application.h
    src/core/window.cpp
    src/core/window.h
    src/core/layer.h
    src/core/log.cpp
    src/core/log.h
    src/core/imgui_layer.cpp
    src/core/imgui_layer.h

    vendor/stb/stb_image.cpp
    vendor/stb/stb_image.h
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
target_link_libraries(core assimp)

target_include_directories(core PUBLIC "src" "vendor/stb")
