#pragma once
#include "Core.h"
#include "ShapeObject.h"
#include "Component.h"

class Actor : public Core
{
	set<Component*> components;

public:
	Actor();
	virtual ~Actor();

public:
	#pragma region Component
	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	template<typename T>
	T* GetComponent()
	{
		for (Component* _component : components)
		{
			if (is_same_v<decltype(_component), T>) return dynamic_cast<T>(_component);
		}

		return nullptr;
	}
	#pragma endregion

	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

private: 
	void Register();
};

