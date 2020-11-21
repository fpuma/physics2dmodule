#pragma once

#include <graphics/graphicdefinitions.h>
#include <optional>

namespace puma::gfx
{
    class Texture
    {
    public:
        Texture() {}
        Texture( const TextureHandle& _textureHandle, Rect _originalSize )
            : m_textureHandle( _textureHandle )
            , m_originalSize( _originalSize )
        {}

        bool                    isValid()           const { return m_textureHandle != nullptr; }
        TextureHandle           getHandle()         const { return m_textureHandle; }
        Rect                    getOriginalSize()   const { return m_originalSize; }

    private:

        TextureHandle m_textureHandle = nullptr;
        Rect m_originalSize = {};
    };
}