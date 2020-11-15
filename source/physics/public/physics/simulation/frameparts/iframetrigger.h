#pragma once

#include <physics/simulation/frameparts/iframepart.h>

namespace puma::physics
{
    class IFrameTrigger : public IFramePart
    {
    public:

        virtual ~IFrameTrigger(){}
    };
}