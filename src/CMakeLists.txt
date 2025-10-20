#
# core
#

set(CORE_SOURCES
    core/events/application_event.h
    core/events/event.h
    core/events/key_codes.h
    core/events/key_event.h
    core/events/mouse_codes.h
    core/events/mouse_event.h

    core/renderer/camera.cpp
    core/renderer/camera.h
    core/renderer/mesh.cpp
    core/renderer/mesh.h
    core/renderer/model.cpp
    core/renderer/model.h
    core/renderer/shader.cpp
    core/renderer/shader.h
    core/renderer/texture.cpp
    core/renderer/texture.h
    core/renderer/utils.cpp
    core/renderer/utils.h

    core/application.cpp
    core/application.h
    core/window.cpp
    core/window.h
    core/layer.h
    core/log.cpp
    core/log.h
    core/imgui_layer.cpp
    core/imgui_layer.h
)

add_library(core STATIC)

target_sources(core PRIVATE ${CORE_SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(core spdlog)
target_link_libraries(core glfw)
target_link_libraries(core glad)
target_link_libraries(core glm)
target_link_libraries(core imguilib)
target_link_libraries(core assimp)
target_link_libraries(core stb_image)

#
# app
#

set(APP_SOURCES
    app/main.cpp
    app/model_layer.cpp
    app/model_layer.h
)

add_executable(app)

target_sources(app PRIVATE ${APP_SOURCES})

target_link_libraries(app core)

include_directories(PUBLIC "." "${CMAKE_SOURCE_DIR}/vendor")

# Set working directory for VS debugger
set_target_properties(app PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
