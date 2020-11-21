#pragma once
#include <graphics/texture.h>

namespace puma::gfx
{
    class ITextureManager
    {
    public:
        ITextureManager() = default;
        virtual ~ITextureManager() = default;

        ITextureManager( const ITextureManager& ) = delete;
        ITextureManager& operator=( const ITextureManager& ) = delete;

        virtual Texture loadTexture( const char* _path ) = 0;
        virtual FontHandle loadFont( const char* _fontPath ) = 0;
        virtual Texture textToTexture( const char* _text, FontHandle _font, Color _color ) = 0;
    };
}