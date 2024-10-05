//
// Created by basavaraj on 10/5/24.
//

#ifndef OPENGL_PROJECT_VERTEXBUFFERLAYOUT_HPP
#define OPENGL_PROJECT_VERTEXBUFFERLAYOUT_HPP
#include <vector>
#include "Renderer.hpp"

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalised;
    static unsigned int GetSizeOfType( unsigned int type){

        switch (type) {

            case GL_FLOAT:         return 4;
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<class T>
    void Push(unsigned int count);
    inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
};

#endif //OPENGL_PROJECT_VERTEXBUFFERLAYOUT_HPP
