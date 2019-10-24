cmake_minimum_required(VERSION 3.8)
project(opengl)

# generates Shaders.hpp containing all shaders from ./shaders as string literals
add_subdirectory(embed)

# tinyobjloader - loads .obj 3d mdels
add_subdirectory(tinyobjloader)

# GLM - GLSL-like types
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(glm)

# GLEW - load OpenGl
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "" FORCE)
add_subdirectory(glew)

# GLFW - create window and context for OpenGL
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# PROJECTS
add_subdirectory(proj1)
