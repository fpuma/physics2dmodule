#pragma once

#include <application/commondefinitions.h>

namespace puma::app
{
    class IRenderer;

    class IWindow : public NonCopyable
    {
    public:

        virtual ~IWindow() {}

        virtual IRenderer* getRenderer() = 0;
        virtual const IRenderer* getRenderer() const = 0;

        virtual Extent getExtent() const = 0;

        virtual WindowHandle getWindowHandle() const = 0;

        virtual bool isValid() const = 0;
    };
}