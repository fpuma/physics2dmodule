#pragma once

namespace puma::physics
{
    using CollisionIndex = u32;
    constexpr CollisionIndex kDefaultCollisionID = 0;
    constexpr u32 kMaxCollisionCateogries = 16;
    using CollisionRelation = std::pair<CollisionIndex, CollisionIndex>;
    using CollisionCompatibility = std::vector<CollisionRelation>;
    using CollisionMask = u16;
    using UserCollisionData = void*;
}