#pragma once
#include <physics/simulation/frames/iframe.h>

namespace puma::physics
{
    class IStaticFrame : public IFrame
    {
    public:

        virtual ~IStaticFrame() {}
    };
}