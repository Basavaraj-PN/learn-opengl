
#ifndef OPENGL_PROJECT_RENDERER_HPP
#define OPENGL_PROJECT_RENDERER_HPP

#include <csignal>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

#endif //OPENGL_PROJECT_RENDERER_HPP
