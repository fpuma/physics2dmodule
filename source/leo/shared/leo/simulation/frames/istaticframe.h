#pragma once
#include <leo/simulation/frames/iframe.h>

namespace puma::leo
{
    class IStaticFrame : public IFrame
    {
    public:

        virtual ~IStaticFrame() {}
    };
}