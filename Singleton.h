#pragma once
#include "CoreMinimal.h"

template <typename Type>
class Singleton
{
public:
	FORCEINLINE static Type& GetInstance()
	{
		static Type _instance;
		return _instance;
	}
};
