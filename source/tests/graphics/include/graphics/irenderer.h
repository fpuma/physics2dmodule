#pragma once

namespace puma::app
{
    class Texture;
    struct Extent;
    struct Color;

    class IRenderer : public NonCopyable
    {
    public:
        virtual ~IRenderer() = default;

        virtual bool isValid() const = 0;
        virtual void beginRender() = 0;
        virtual void endRender() = 0;

        virtual void setDefaultBackgroundColor( Color _bgColor ) = 0;

        virtual const RendererHandle getRendererHandle() const = 0;
        virtual RendererHandle getRendererHandle() = 0;

        virtual void renderTexture( const Texture& _texture, const Extent& _textureExtent, const Extent& _targetExtent, float _rotation ) const = 0;

        virtual void renderText( const s32 _xPos, const s32 _yPos, const char* _text ) const = 0;
		virtual void renderPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color ) = 0;
		virtual void renderSolidPolygon( const s16* _xCoords, const s16* _yCoords, s32 vertexCount, const Color& _color ) = 0;
		virtual void renderCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color ) = 0;
		virtual void renderSolidCircle( const s32 _xCenter, const s32 _yCenter, s32 _radius, const Color& _color ) = 0;
        virtual void renderSegment( const s32 _x1, const s32 _y1, const s32 _x2, const s32 _y2, const Color& _color ) = 0;
		
    };
}