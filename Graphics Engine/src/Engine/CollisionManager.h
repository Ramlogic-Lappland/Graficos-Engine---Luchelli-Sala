#pragma once
#include "EngineAPI.h"
#include "Entity2D.h"
#include <vector>

struct CollisionContact
{
    Entity2D* first = nullptr;
    Entity2D* second = nullptr;
};

class ENGINE_API CollisionManager
{
public:
    // Call after movement and before drawing; returns overlapping pairs.
    std::vector<CollisionContact> Update(const std::vector<Entity2D*>& colliders) const;

private:
    static bool Overlap(const AABB& a, const AABB& b);
    static void Resolve(Entity2D& a, Entity2D& b, const AABB& boxA, const AABB& boxB);
};
