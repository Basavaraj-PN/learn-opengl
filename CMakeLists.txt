# Get CMake PreDefined Variables https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html
# This CMake File for OpenGL Projects is compiled by Kushagra
# I do not claim that this is the best CMake Configuration you will get but it does work.

cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(Application)

# Set the policy to use the modern GLVND libraries
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add all Header Files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Find the Required Packages
find_package(OpenGL REQUIRED)

# Variables for Paths of External Libraries
set(GLFW_ROOT_DIR external/glfw)
set(GLAD_ROOT_DIR external/glad)

# Add the External Libraries / Files Directory
add_subdirectory(${GLFW_ROOT_DIR})
add_subdirectory(${GLAD_ROOT_DIR})

# Add the Include Directories for the Libraries / Files
# Used for adding #include into the cpp files
target_include_directories(${PROJECT_NAME}
        PUBLIC ${GLFW_ROOT_DIR}/include
        PUBLIC ${GLAD_ROOT_DIR}/include/glad
)

# Add the Libs to the Linker for the Project
# Platform-specific linking
if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL opengl32)
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} glfw glad OpenGL::GL)
endif ()


# EXPLANATION FOR SOME STUFF
# GLOB_RECURSE -> Recursively go through all subdirectories
#		of the given path and get all the files matching the extension provided
# file() -> Store the Files matching the RegEx into a variable
# set() -> Alternative to file() if you want to set variables for a custom behaviour
