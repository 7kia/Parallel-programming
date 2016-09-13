#pragma once

struct Vector2UL
{
	Vector2UL();
	Vector2UL(size_t firstNumber, size_t secondNumber);
	bool operator==(const Vector2UL &right) const;

	size_t x;
	size_t y;
};