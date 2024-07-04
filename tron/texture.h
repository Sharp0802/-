#pragma once

#include <pch.h>

namespace tron
{
    enum TextureFlag
    {
        TF_MIPMAP = SOIL_FLAG_MIPMAPS,
        TF_REPEAT = SOIL_FLAG_TEXTURE_REPEATS
    };

    class Texture
    {
        std::shared_ptr<GLuint> _texture;

    public:
        Texture(const std::string& path, TextureFlag flags);
    };
}
