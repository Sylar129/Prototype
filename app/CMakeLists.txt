#
# app
#

set(SOURCES
    src/main.cpp
    src/app_layer.h
    src/app_layer.cpp
)

add_executable(app)

target_sources(app PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(app core)

target_include_directories(app PRIVATE src)

# Set working directory for VS debugger
set_target_properties(app PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/app"
)