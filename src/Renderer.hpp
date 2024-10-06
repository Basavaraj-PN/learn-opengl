
#ifndef OPENGL_PROJECT_RENDERER_HPP
#define OPENGL_PROJECT_RENDERER_HPP

#include <csignal>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

class Shader;

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);


class Renderer {

public:
    void Clear() const;

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};

#endif //OPENGL_PROJECT_RENDERER_HPP


