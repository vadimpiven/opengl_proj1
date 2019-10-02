cmake_minimum_required(VERSION 3.8)
project(opengl C CXX)

# set global variables
set(CMAKE_CXX_STANDARD 17)

# generates Shaders.hpp containing all shaders from ./shaders as string literals
file(GLOB SHADERS shaders/*.vert shaders/*.frag)
add_subdirectory(embed)
add_custom_target("${PROJECT_NAME}_shaders"
        COMMAND embed_shaders "${SHADERS}"
        BYPRODUCTS Shader.hpp
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Generating embeded shaders"
        VERBATIM)

# compile sources
file(GLOB SOURCES *.cpp)
if(MSVC) # get rid of console window
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /entry:mainCRTStartup")
endif(MSVC)
add_executable("${PROJECT_NAME}" "${SOURCES}")
add_dependencies("${PROJECT_NAME}" "${PROJECT_NAME}_shaders")

# Assimp - load 3D objects
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(assimp) # https://github.com/assimp/assimp
target_include_directories("${PROJECT_NAME}" PRIVATE assimp/include)
target_link_libraries("${PROJECT_NAME}" assimp)

# SOIL - open textures
add_subdirectory(soil) # https://github.com/paralin/soil
target_include_directories("${PROJECT_NAME}" PRIVATE soil/inc)
target_link_libraries("${PROJECT_NAME}" soil)

# GLM - GLSL-like types
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(glm) # https://github.com/g-truc/glm
target_include_directories("${PROJECT_NAME}" PRIVATE glm/glm)
target_link_libraries("${PROJECT_NAME}" glm_static)

# OpenGL - draw graphics
find_package(opengl 3.3 REQUIRED)
target_include_directories("${PROJECT_NAME}" PRIVATE "${OPENGL_INCLUDE_DIRS}")
target_link_libraries("${PROJECT_NAME}" "${OPENGL_LIBRARIES}")

# GLEW - load OpenGl
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "" FORCE)
add_subdirectory(glew) # https://github.com/Perlmint/glew-cmake
target_include_directories("${PROJECT_NAME}" PRIVATE glew/include)
target_link_libraries("${PROJECT_NAME}" libglew_static)

# GLFW - create window and context for OpenGL
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw) # https://github.com/glfw/glfw
target_link_libraries("${PROJECT_NAME}" glfw)

# copy resources
file(COPY "${PROJECT_SOURCE_DIR}/resources/" DESTINATION "${PROJECT_BINARY_DIR}")
