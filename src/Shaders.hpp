
#ifndef OPENGL_PROJECT_SHADERS_HPP
#define OPENGL_PROJECT_SHADERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "Renderer.hpp"
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader {
private:
    unsigned int m_RenderID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string &filepath);

    ~Shader();

    void Bind() const;

    void Unbind() const;

    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    void SetUniform1f(const std::string &name, float value);

    int GetUniformLocation(const std::string &name);

    ShaderProgramSource ParseShader(const std::string &filepath);

    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
};

#endif //OPENGL_PROJECT_SHADERS_HPP
