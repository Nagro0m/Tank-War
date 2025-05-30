#include "CollisionComponent.h"
#include "CollisionManager.h"

CollisionStep CollisionComponent::ComputeOthersStep(Actor* _other, const CollisionStep& _step)
{
    if ((othersStep.contains(_other) && othersStep[_other] == CS_ENTER) || othersStep[_other] == CS_UPDATE)
    {
		othersStep[_other] = CS_UPDATE;
	}
	else
	{
		othersStep[_other] = _step;
	}
	return othersStep[_other];

}

CollisionComponent::CollisionComponent(Actor* _owner, const string& _channelName, const int _status, const CollisionType& _type) : Component(_owner)
{
	channelName = _channelName;
	type = _type;
	status = _status;
	enable = false;
}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent& _other) : Component(_owner)
{
	channelName = _other.channelName;
	type = _other.type;
	status = _other.status;
	responses = _other.responses;
	enable = _other.enable;
}

void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	//CheckCollision();

	if (channelName != "NONE")
	{
		CheckCollision();
	}
}

void CollisionComponent::CheckCollision()
{
    if (!enable) return;
    if (!(status & IS_PHYSIC)) return;
    const set<CollisionComponent*>& _allComponent = M_COLLISION.GetAllCollisionComponents();
    const MeshActor* _ownerMesh = Cast<MeshActor>(owner);
    if (!_ownerMesh) return;
    const Vector2f& _ownerPos = _ownerMesh->GetPosition();
    if (_ownerMesh->GetMesh()->GetShape()->GetData().type == ShapeObjectType::SOT_CIRCLE) return;
    const Vector2f& _ownerSize = _ownerMesh->GetMesh()->GetShape()->GetData().data.rectangleData->size;

    for (CollisionComponent* _otherComponent : _allComponent)
    {
        if (_otherComponent == this) continue;
        if (M_COLLISION.ContainPair(owner, _otherComponent->owner)) continue;

        const string& _otherName = _otherComponent->GetChannelName();
        if (!responses.contains(_otherName)) continue;
        if (_otherComponent->responses.empty()) continue;

        const CollisionType& _otherResponse = responses.at(_otherName);
        const CollisionType& _ownerResponse = _otherComponent->responses.at(channelName);
        if (_otherResponse == CT_NONE) continue;

        MeshActor* _otherMesh = Cast<MeshActor>(_otherComponent->owner);
        const Vector2f& _otherPos = _otherMesh->GetPosition();
        if (_ownerMesh->GetMesh()->GetShape()->GetData().type == ShapeObjectType::SOT_CIRCLE) continue;

        const Vector2f& _otherSize = _otherMesh->GetMesh()->GetSize();

        bool _isColliding = false;
        FloatRect intersection = {};

        if (_ownerSize != Vector2f{ 0.f, 0.f } && _otherSize != Vector2f{ 0.f, 0.f })
        {
            OBB ownerOBB, otherOBB;
            Vector2f ownerCenter = _ownerPos + _ownerSize / 2.f;
            Vector2f otherCenter = _otherPos + _otherSize / 2.f;

            ComputeOBB(ownerCenter, _ownerSize, _ownerMesh->GetRotation().asDegrees(), ownerOBB);
            ComputeOBB(otherCenter, _otherSize, _otherMesh->GetRotation().asDegrees(), otherOBB);

            auto Normalize = [](const Vector2f& v) -> Vector2f {
                float len = std::sqrt(v.x * v.x + v.y * v.y);
                return len != 0.f ? Vector2f{ v.x / len, v.y / len } : v;
                };

            auto ProjectOntoAxis = [](const OBB& obb, const Vector2f& axis, float& min, float& max) {
                min = max = obb.corners[0].x * axis.x + obb.corners[0].y * axis.y;
                for (int i = 1; i < 4; ++i) {
                    float proj = obb.corners[i].x * axis.x + obb.corners[i].y * axis.y;
                    if (proj < min) min = proj;
                    if (proj > max) max = proj;
                }
                };

            std::vector<Vector2f> axes;
            for (int i = 0; i < 4; ++i) {
                Vector2f edge = {
                    ownerOBB.corners[(i + 1) % 4].x - ownerOBB.corners[i].x,
                    ownerOBB.corners[(i + 1) % 4].y - ownerOBB.corners[i].y
                };
                axes.push_back(Normalize(Vector2f{ -edge.y, edge.x }));
            }

            for (int i = 0; i < 4; ++i) {
                Vector2f edge = {
                    otherOBB.corners[(i + 1) % 4].x - otherOBB.corners[i].x,
                    otherOBB.corners[(i + 1) % 4].y - otherOBB.corners[i].y
                };
                axes.push_back(Normalize(Vector2f{ -edge.y, edge.x }));
            }

            _isColliding = true;
            float minOverlap = std::numeric_limits<float>::max();
            Vector2f mtvAxis;

            for (const auto& axis : axes) {
                float minA, maxA, minB, maxB;
                ProjectOntoAxis(ownerOBB, axis, minA, maxA);
                ProjectOntoAxis(otherOBB, axis, minB, maxB);

                if (maxA < minB || maxB < minA) {
                    _isColliding = false;
                    break;
                }
                else {
                    float overlap = std::min(maxA, maxB) - std::max(minA, minB);
                    if (overlap < minOverlap) {
                        minOverlap = overlap;
                        mtvAxis = axis;
                        // Ajuste direction pour aller de owner vers other
                        Vector2f d = otherCenter - ownerCenter;
                        if ((d.x * mtvAxis.x + d.y * mtvAxis.y) < 0)
                            mtvAxis = Vector2f{ -mtvAxis.x, -mtvAxis.y };
                    }
                }
            }

            if (_isColliding) {
                Vector2f mtv = mtvAxis * minOverlap;

                // Tu peux utiliser `mtv` pour la résolution
                // Pour l’instant, on le visualise avec un petit rectangle au centre
                Vector2f center = (ownerCenter + otherCenter) / 2.f;
                intersection.position = center + mtv * 0.5f - Vector2f{ 2.f, 2.f };
                intersection.size = Vector2f{ 4.f, 4.f };

                // Exemple : appliquer MTV à l’un des objets
                // _ownerPos += mtv; // pour pousser le owner hors de la collision
            }
        }
        else
        {
            // === Cas CERCLE ===
            Vector2f centerA = _ownerPos;
            Vector2f centerB = _otherPos;

            float radiusA = std::max(_ownerSize.x, _ownerSize.y) / 2.f;
            float radiusB = std::max(_otherSize.x, _otherSize.y) / 2.f;

            float dx = centerA.x - centerB.x;
            float dy = centerA.y - centerB.y;
            float distanceSq = dx * dx + dy * dy;
            float combinedRadius = radiusA + radiusB;

            _isColliding = distanceSq <= combinedRadius * combinedRadius;

            if (_isColliding)
            {
                // Pas de vraie "intersection" pour les cercles, mais on remplit la struct
                intersection.position = Vector2f{ std::min(centerA.x, centerB.x), std::min(centerA.y, centerB.y) };
                intersection.size = Vector2f{ combinedRadius, combinedRadius }; // valeur symbolique
            }
        }

        if (_isColliding)
        {
            CollisionStep _step = ComputeOthersStep(_otherMesh, CS_ENTER);
            const CollisionData& _ownerData = { owner, _ownerResponse, intersection, _step };
            const CollisionData& _otherData = { _otherMesh, _otherResponse, intersection, _step };
            M_COLLISION.Collide(_ownerData, _otherData);
        }
        else if (othersStep.contains(_otherComponent->owner))
        {
            CollisionStep _step = ComputeOthersStep(_otherMesh, CS_EXIT);
            const CollisionData& _ownerData = { owner, _ownerResponse, {}, _step };
            const CollisionData& _otherData = { _otherMesh, _otherResponse, {}, _step };
            M_COLLISION.Collide(_ownerData, _otherData);
            othersStep.erase(_otherMesh);
        }
    }
}