#pragma once
#include "CoreMinimal.h"



template <typename Class>
class Singleton
{
public:
	FORCEINLINE static Class& GetInstance()
	{
		static Class _instance;
		return _instance;
	}
};
