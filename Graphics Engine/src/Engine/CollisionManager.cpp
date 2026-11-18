#include "CollisionManager.h"
#include <algorithm>

bool CollisionManager::Overlap(const AABB& a, const AABB& b)
{
    // Touching edges are not counted as penetrating.
    return a.min.x < b.max.x && a.max.x > b.min.x && a.min.y < b.max.y && a.max.y > b.min.y;
}

void CollisionManager::Resolve(Entity2D& a, Entity2D& b, const AABB& boxA, const AABB& boxB)
{
    if (a.IsTrigger() || b.IsTrigger() || (a.IsStaticCollider() && b.IsStaticCollider()))
        return;

    const float overlapX = std::min(boxA.max.x, boxB.max.x) - std::max(boxA.min.x, boxB.min.x);
    const float overlapY = std::min(boxA.max.y, boxB.max.y) - std::max(boxA.min.y, boxB.min.y);
    if (overlapX <= 0.0f || overlapY <= 0.0f)
        return;

    const glm::vec2 centerA = (boxA.min + boxA.max) * 0.5f;
    const glm::vec2 centerB = (boxB.min + boxB.max) * 0.5f;

    glm::vec2 correction(0.0f);
    if (overlapX < overlapY)
        correction.x = (centerA.x < centerB.x ? -overlapX : overlapX);
    else
        correction.y = (centerA.y < centerB.y ? -overlapY : overlapY);

    if (a.IsStaticCollider())
    {
        b.SetPosition(b.GetPosX() - correction.x, b.GetPosY() - correction.y);
    }
    else if (b.IsStaticCollider())
    {
        a.SetPosition(a.GetPosX() + correction.x, a.GetPosY() + correction.y);
    }
    else
    {
        if (a.GetWeight() > b.GetWeight())
        {
            b.SetPosition(
                b.GetPosX() - correction.x,
                b.GetPosY() - correction.y
            );
        }
        else if (b.GetWeight() > a.GetWeight())
        {
            a.SetPosition(
                a.GetPosX() + correction.x,
                a.GetPosY() + correction.y
            );
        }
        else
        {
            const glm::vec2 half = correction * 0.5f;

            a.SetPosition(
                a.GetPosX() + half.x,
                a.GetPosY() + half.y
            );

            b.SetPosition(
                b.GetPosX() - half.x,
                b.GetPosY() - half.y
            );
        }
    }
}

std::vector<CollisionContact> CollisionManager::Update(const std::vector<Entity2D*>& colliders) const
{
    std::vector<CollisionContact> contacts;
    for (size_t i = 0; i < colliders.size(); ++i)
    {
        Entity2D* a = colliders[i];
        if (!a || !a->IsActive() || !a->IsCollisionEnabled()) continue;

        for (size_t j = i + 1; j < colliders.size(); ++j)
        {
            Entity2D* b = colliders[j];
            if (!b || !b->IsActive() || !b->IsCollisionEnabled()) continue;

            const AABB boxA = a->GetAABB();
            const AABB boxB = b->GetAABB();
            if (!Overlap(boxA, boxB)) continue;

            contacts.push_back({ a, b });
            Resolve(*a, *b, boxA, boxB);
        }
    }
    return contacts;
}
