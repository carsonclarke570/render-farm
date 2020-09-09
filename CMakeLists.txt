cmake_minimum_required(VERSION 3.12)
project(Daybreak)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EAMPLES OFF)
option(GLFW_BUILD_TEST OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)

# glad
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glad)

# Includes
include_directories(
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/libs/assimp/include/
        ${PROJECT_SOURCE_DIR}/libs/stb/include/
        ${PROJECT_SOURCE_DIR}/libs/glad/include/
        ${PROJECT_SOURCE_DIR}/libs/glfw/include/
)

# Sources
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h ${PROJECT_SOURCE_DIR}/libs/stb/include/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SHADERS ${PROJECT_SOURCE_DIR}/res/shaders/*.frag ${PROJECT_SOURCE_DIR}/res/shaders/*.geom ${PROJECT_SOURCE_DIR}/res/shaders/*.vert)
file(GLOB_RECURSE TEXTURES ${PROJECT_SOURCE_DIR}/res/textures/*.png)
file(GLOB_RECURSE MODELS ${PROJECT_SOURCE_DIR}/res/models/*.obj)

file(COPY ${SHADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TEXTURES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${MODELS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

source_group("headers" FILES ${HEADERS})
source_group("sources" FILES ${SOURCES})
source_group("shaders" FILES ${SHADERS})

add_definitions(
        -DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
        glfw
        ${GLFW_LIBRARIES}
        glad
)
