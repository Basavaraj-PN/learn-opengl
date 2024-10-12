#include <iostream>
#include <glad/glad.h>
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shaders.hpp"
#include "Texture.hpp"
#include "GLUtils.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include <GLFW/glfw3.h> // Will drag system OpenGL headers
float IncrementRedChannel();

int main() {

    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
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
    glfwSwapInterval(1); // Enable vsync


    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {        //3positions, 3colors, 2texture
        float vertices[] = {
                0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0, 0.0f, 1.0f,
        };
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        VertexArray va;
        VertexBuffer vb(vertices, 4 * 8 * sizeof(float));
        VertexBufferLayout layout;
        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 mvp = proj * view;

        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        Shader shader("../res/shaders/Basic.glsl");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);

        Texture texture("../res/texture/green.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;



        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        while (!glfwWindowShouldClose(window)) {

            GLCall(processInput(window));
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }


            renderer.Draw(va, ib, shader);
            view = glm::translate(glm::mat4(1.0f), glm::vec3(std::sin(glfwGetTime()), std::cos(glfwGetTime()), std::sin(glfwGetTime())));
            mvp = proj * view;
            shader.SetUniformMat4f("u_MVP", mvp);
            {
                const auto r = IncrementRedChannel();
                shader.SetUniform4f("u_Color", r, r, r, 1.0f);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }
}
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
