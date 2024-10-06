#include <iostream>
#include <glad/glad.h>
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shaders.hpp"

float IncrementRedChannel();

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
            0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0,
            0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0,
            -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,
            -0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    IndexBuffer ib(indices, 6);

    layout.Push<float>(3);
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);

    Shader shader("../res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {

        GLCall(processInput(window));
        renderer.Clear();
        renderer.Draw(va, ib, shader);
        {
            const auto r = IncrementRedChannel();
            shader.SetUniform4f("u_Color", r, 1.0f - r, r, 1.0f);
        }
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}

float IncrementRedChannel() {
    static float r = 0.0f;
    static float increment = 0.01f; // Consistent increment value

    // Clamp the value within 0.0 and 1.0 and change direction at boundaries
    r += increment;
    if (r >= 1.0f) {
        r = 1.0f;
        increment = -0.01f;
    } else if (r <= 0.0f) {
        r = 0.0f;
        increment = 0.01f;
    }

    return r;
}
