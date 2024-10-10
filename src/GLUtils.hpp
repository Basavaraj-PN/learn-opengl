#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <csignal>


#ifdef _WIN32
#define TRAP __debugbreak()
#else
#define TRAP raise(SIGTRAP)
#endif

#define ASSERT(x) if (!(x)) TRAP;

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);
