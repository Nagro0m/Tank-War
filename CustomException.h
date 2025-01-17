#pragma once
#include "CoreMinimal.h"

class CustomException : public exception
{
	using Error = char const*;

private:
	NO_DISCARD virtual Error what() const override
	{
		return Super::what();
	}

public:
	NO_DISCARD Error What() const
	{
		return what();
	}

public:
	CustomException(const Error _error) : exception(_error)
	{

	}
};