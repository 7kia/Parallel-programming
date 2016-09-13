#include "stdafx.h"
#include "MyFunctions.h"

Vector2UL::Vector2UL()
	: x(0)
	, y(0)
{
}

Vector2UL::Vector2UL(size_t firstNumber, size_t secondNumber)
	: x(firstNumber)
	, y(secondNumber)
{
}

bool Vector2UL::operator==(const Vector2UL & right) const
{
	return (x == right.x) && (y == right.y);
}