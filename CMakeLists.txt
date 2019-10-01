cmake_minimum_required(VERSION 3.8)
project(opengl CXX)

# set global variables
set(CMAKE_CXX_STANDARD 17)

# generates Shaders.hpp containing all shaders from ./shaders as string literals
file(GLOB SHADERS shaders/*.vert shaders/*.frag)
add_subdirectory(embed)
add_custom_target("${PROJECT_NAME}_shaders"
        COMMAND embed_shaders "${SHADERS}"
        BYPRODUCTS Shaders.hpp
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Generating embeded shaders"
        VERBATIM)

# compile sources
file(GLOB SOURCES *.cpp)
if(MSVC) # get rid of console window
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /entry:mainCRTStartup")
endif(MSVC)
add_executable("${PROJECT_NAME}" "${SOURCES}" Rectangle.cpp Rectangle.hpp Object.cpp)
add_dependencies("${PROJECT_NAME}" "${PROJECT_NAME}_shaders")

# OpenGL
find_package(opengl 3.3 REQUIRED)
target_include_directories("${PROJECT_NAME}" PRIVATE "${OPENGL_INCLUDE_DIRS}")
target_link_libraries("${PROJECT_NAME}" "${OPENGL_LIBRARIES}")

# GLEW
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "" FORCE)
add_subdirectory(glew) # https://github.com/Perlmint/glew-cmake
target_include_directories("${PROJECT_NAME}" PRIVATE glew/include)
target_link_libraries("${PROJECT_NAME}" libglew_static)

# GLFW
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw) # https://github.com/glfw/glfw
target_link_libraries("${PROJECT_NAME}" glfw)

# copy resources
file(COPY "${PROJECT_SOURCE_DIR}/resources/" DESTINATION "${PROJECT_BINARY_DIR}")
