#pragma once

#include <memory>

namespace puma::gfx
{
    class IRenderer;
    class ITextureManager;
    struct Extent;

    class IGraphics
    {
    public:
        virtual ~IGraphics() {}

        static std::unique_ptr<IGraphics> create();

        virtual void init( const Extent& _extent, const char* _windowName ) = 0;
        virtual void uninit() = 0;
        virtual void update() = 0;

        virtual const IRenderer* getRenderer() const = 0;
        virtual       IRenderer* getRenderer() = 0;

        virtual const ITextureManager*   getTextureManager() const = 0;
        virtual       ITextureManager*   getTextureManager() = 0;

        virtual Extent getWindowExtent() const = 0;
        virtual bool shouldQuit() const = 0;

        virtual void consumeSdlEvents() = 0;
        virtual void peekSdlEvents() = 0;

    };
}