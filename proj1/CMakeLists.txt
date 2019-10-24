cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}_proj1 C CXX)

# set global variables
set(CMAKE_CXX_STANDARD 17)

# generates Shaders.hpp containing all shaders from ./shaders as string literals
file(GLOB SHADERS shaders/*.vert shaders/*.frag)
add_custom_target("${PROJECT_NAME}_shaders"
        COMMAND embed_shaders "${SHADERS}"
        BYPRODUCTS Shader.hpp
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Generating embeded shaders"
        VERBATIM)

# compile sources
file(GLOB SOURCES *.cpp *.hpp)
if(MSVC) # get rid of console window if compiling on Windows with Visual Studio
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /entry:mainCRTStartup")
endif(MSVC)
add_executable("${PROJECT_NAME}" WIN32 "${SOURCES}")
add_dependencies("${PROJECT_NAME}" "${PROJECT_NAME}_shaders")

# tinyobjloader - loads .obj 3d mdels
target_include_directories("${PROJECT_NAME}" PRIVATE ../tinyobjloader)
target_link_libraries("${PROJECT_NAME}" tinyobjloader)

# STB - image loader for textures
target_include_directories("${PROJECT_NAME}" PRIVATE  ../stb)

# GLM - GLSL-like types
target_include_directories("${PROJECT_NAME}" PRIVATE ../glm/glm)
target_link_libraries("${PROJECT_NAME}" glm_static)

# OpenGL - draw graphics
find_package(opengl 3.3 REQUIRED)
target_include_directories("${PROJECT_NAME}" PRIVATE "${OPENGL_INCLUDE_DIRS}")
target_link_libraries("${PROJECT_NAME}" "${OPENGL_LIBRARIES}")

# GLEW - load OpenGl
target_include_directories("${PROJECT_NAME}" PRIVATE ../glew/include)
target_link_libraries("${PROJECT_NAME}" libglew_static)

# GLFW - create window and context for OpenGL
target_link_libraries("${PROJECT_NAME}" glfw)

# copy resources
file(COPY "resources/" DESTINATION "${PROJECT_BINARY_DIR}")
