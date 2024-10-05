//
// Created by basavaraj on 10/5/24.
//

#ifndef OPENGL_PROJECT_VERTEXARRAY_HPP
#define OPENGL_PROJECT_VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
    unsigned int m_RenderID;
public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;

    void Unbind() const;
};


#endif //OPENGL_PROJECT_VERTEXARRAY_HPP
