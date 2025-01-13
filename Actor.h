#pragma once
#include "Core.h"
#include "ShapeObject.h"
#include "Component.h"

class Actor : public Core
{
	ShapeObject* shape;
	set<Component*> components;

public:
	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}
	FORCEINLINE ShapeObject* GetShape()
	{
		return shape;
	}

public:
	Actor(const float _radius, const string& _path,
		const IntRect _rect = IntRect(), const int _pointCount = 30);
	//Rectangle
	Actor(Vector2f _size, const string& _path,
		const IntRect _rect = IntRect());

	~Actor();

private:
	void Register();
public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

public:
	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);

	template<typename Type>
	Type* GetComponent()
	{
		for (Component* _component : components)
		{
			if (is_same_v<decltype(_component), Type>)
			{
				return dynamic_cast<Type>(_component);
			}
		}

		return nullptr;
	}
};