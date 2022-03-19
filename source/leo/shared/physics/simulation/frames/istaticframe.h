#pragma once
#include <physics/simulation/frames/iframe.h>

namespace puma::leo
{
    class IStaticFrame : public IFrame
    {
    public:

        virtual ~IStaticFrame() {}
    };
}