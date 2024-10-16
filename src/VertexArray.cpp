
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();
    unsigned int offset = 0;
    const auto &elements = layout.GetElements();
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        GLCall(glEnableVertexAttribArray(i));

        GLCall(
                glVertexAttribPointer(i, element.count, element.type,
                                      element.normalised, layout.GetStride(),
                                      (const void *) offset)
        );

        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}
