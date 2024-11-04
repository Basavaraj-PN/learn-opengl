//int
// Created by basavaraj on 10/5/24.
//

#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout()
        : m_Stride(0) {

}

VertexBufferLayout::~VertexBufferLayout() {

}

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

template<class T>
void Push(unsigned int count){
//    static_assert(false);
    static_assert(std::is_integral<T>::value, "Push only supports integral types.");
}