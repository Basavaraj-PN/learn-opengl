
#include <glad/glad.h>
#include <iostream>
#include "Renderer.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shaders.hpp"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
            0.5f, 0.5f, 0.0f,     0.0, 0.0, 1.0,
            0.5f, -0.5f, 0.0f,     0.0, 0.0, 1.0,
            -0.5f, -0.5f, 0.0f,    1.0, 0.0, 0.0,
            -0.5f, 0.5f, 0.0f,     1.0, 0.0, 0.0
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    {


        VertexArray va;
        VertexBuffer vb(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        float r = 0.0f;
        float increment = 0.05f;
        while (!glfwWindowShouldClose(window)) {

            GLCall(processInput(window));
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            va.Bind();
            ib.Bind();
            shader.SetUniform4f("u_Color", r, 1.0f - r, r, 1.0f);
            if (r > 1.0f)
                increment = -0.01;
            else if (r < 0.0f)
                increment = 0.01f;
            r += increment;

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // Correct function and parameters

            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}

