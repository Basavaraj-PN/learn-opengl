cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set policy for OpenGL GLVND
if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)  # Prefer GLVND
endif()

# Find GLFW package
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Find GLEW package
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

# Add GLAD
add_library(glad ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)


# Add source files
set(SOURCE_FILES src/Application.cpp
        src/Renderer.hpp
        src/Renderer.cpp
        src/VertexBuffer.hpp
        src/VertexBuffer.cpp
        src/IndexBuffer.cpp
        src/IndexBuffer.hpp
        src/VertexArray.cpp
        src/VertexArray.hpp
        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.hpp
        src/Shaders.cpp
        src/Shaders.hpp
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp
        src/Texture.hpp) # Replace with your actual source files

# Create the executable
add_executable(Application ${SOURCE_FILES})

# Link libraries
target_link_libraries(Application OpenGL glfw glad GLEW)

# Include directories
target_include_directories(Application PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)