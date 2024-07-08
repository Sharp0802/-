#include "texture.h"
#include "global.h"

namespace tron
{
    Texture::Texture(const std::string& path, const TextureFlag flags)
    {
        _texture = std::shared_ptr<GLuint>(
            new GLuint(),
            [](const GLuint* p)
            {
                glDeleteTextures(1, p);
            });
        *_texture = SOIL_load_OGL_texture(
            Global::GetPath(path).data(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            flags ^ static_cast<int>(SOIL_FLAG_INVERT_Y));
    }

    void Texture::Use() const
    {
        glBindTexture(GL_TEXTURE_2D, *_texture);
    }
}
