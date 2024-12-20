
#include "Shaders.hpp"
#include <vector>
#include "GLUtils.hpp"

Shader::Shader(const std::string &filepath) : m_RenderID(0), m_Filepath(filepath) {

    ShaderProgramSource source = ParseShader(filepath);
    m_RenderID = CreateProgram(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RenderID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string &name, float value) {

    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string &name, float value) {

    GLCall(glUniform1f(GetUniformLocation(name), value));
}
void Shader::SetUniformMat4f(const std::string &name, glm::mat4 &matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}


void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {

    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string &name) {

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()))
    if (location == -1)
        std::cout << "Warning! uniform " << name << " doesn't exists" << std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}


ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[int(type)] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {

    if(source.empty()){
        std::cout << "ERROR::SHADER::SOURCE_EMPTY" << std::endl;
        return 0;
    }

    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length);
        glGetShaderInfoLog(id, length, nullptr, message.data());
        std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n"
                  << message.data() << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vs == 0 || fs == 0) {
        std::cout << "ERROR::SHADER::" << (vs==0? "VERTEX" :  "FRAGMENT")<<std::endl;
        glDeleteProgram(program);
        return 0; // or handle error accordingly
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length);
        glGetProgramInfoLog(program, length, nullptr, message.data());
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << message.data() << std::endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}



