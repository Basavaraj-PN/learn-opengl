#pragma once


#include <csignal>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shaders.hpp"

class Shader;

class Renderer {

public:
    void Clear() const;

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
