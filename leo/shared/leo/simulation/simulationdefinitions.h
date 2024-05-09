#pragma once

namespace puma::leo
{
    class IWorld;
    
    class IFrame;
    class IDynamicFrame;
    class IStaticFrame;
    class IKinematicFrame;

    class IFramePart;
    class IFrameBody;
    class IFrameTrigger;

    enum class FrameType
    {
        Dynamic,
        Static,
        Kinematic,

        Count,
        Invalid,
    };

    enum class FramePartType
    {
        Body,
        Trigger,

        Count,
        Invalid,
    };
}