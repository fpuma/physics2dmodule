#pragma once

namespace puma::physics
{
    //The sum of these should not exceed 32
    constexpr u8 kWorldIdBitCount = 2;
    constexpr u8 kFrameIdBitCount = 20;
    constexpr u8 kFrameTypeBitCount = 2;
    constexpr u8 kFramePartIdBitCount = 6;
    constexpr u8 kFramePartTypeBitCount = 2;
    //------------------------------------

    constexpr u32 kMaxWorldCount =     ((u32)~0x0 >> ( (8 * sizeof( PhysicsID ))     - kWorldIdBitCount)) + 1;
    constexpr u32 kMaxFrameCount =     ((u32)~0x0 >> ( (8 * sizeof( PhysicsID ))     - kFrameIdBitCount)) + 1;
    constexpr u32 kMaxFramePartCount = ((u32)~0x0 >> ( (8 * sizeof( PhysicsID ))     - kFramePartIdBitCount)) + 1;

}