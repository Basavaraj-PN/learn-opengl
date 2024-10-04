
#ifndef OPENGL_PROJECT_VERTEXBUFFER_HPP
#define OPENGL_PROJECT_VERTEXBUFFER_HPP

class VertexBuffer{
private:
    unsigned int m_RenderId{};
public:
    VertexBuffer(const void *data, unsigned  int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

#endif //OPENGL_PROJECT_VERTEXBUFFER_HPP
