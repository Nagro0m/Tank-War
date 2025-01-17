#pragma once
#include "Singleton.h"
#include "MeshActor.h"

// Comparateur pour trier les MeshActor
struct ActorHash
{
    size_t operator()(const MeshActor* actor) const 
    {
        return hash<int>()(actor->GetRenderMeshToken());
    }
};

struct ActorEqual
{
    bool operator()(const MeshActor* a, const MeshActor* b) const 
    {
        return a->GetRenderMeshToken() == b->GetRenderMeshToken();
    }
};

class ActorManager : public Singleton<ActorManager>
{
private:
    unordered_set<MeshActor*, ActorHash, ActorEqual> allActors;

public:
    FORCEINLINE const unordered_set<MeshActor*, ActorHash, ActorEqual>& GetAllActors() const
    {
        return allActors;
    }

    FORCEINLINE void AddActor(MeshActor* _actor)
    {
        allActors.insert(_actor);
    }

    ~ActorManager();

    virtual void BeginPlay();
    virtual void Tick(const float _deltaTime);
    virtual void BeginDestroy();
};