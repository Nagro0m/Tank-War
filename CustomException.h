#pragma once
#include "CoreMinimal.h"

class CustomException : public exception
{
	using Error = char const*;

public:

    CustomException(const Error _Message) : exception(_Message)
    {

    }

public:
    NO_DISCARD virtual Error what() const override
    {
        return (CAST(string, "Exception => ") + CAST(string, Super::what())).c_str();
    }
private:

    NO_DISCARD virtual Error What() const
    {
        return what();
    }
};