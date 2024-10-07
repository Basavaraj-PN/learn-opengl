
#ifndef OPENGL_PROJECT_TEXTURE_HPP
#define OPENGL_PROJECT_TEXTURE_HPP

#include "Renderer.hpp"
#include <iostream>

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:

    Texture(const std::string &filepath);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind() const;

    [[nodiscard]] inline
    int GetWidth() const { return m_Width; }

    [[nodiscard]] inline int GetHeight() const { return m_Height; }
};

#endif //OPENGL_PROJECT_TEXTURE_HPP
