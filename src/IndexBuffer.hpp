#pragma once

class IndexBuffer {
private:
    unsigned int m_RenderId{};
    unsigned int m_Count{};
public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

    [[nodiscard]] inline unsigned int GetCount() const { return m_Count; };
};
