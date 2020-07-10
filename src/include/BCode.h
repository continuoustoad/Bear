#pragma once
#include <cinttypes>

class BCode
{
public:
	std::uint8_t *Code;

	template<typename X>
	X Get(std::size_t index)
	{
		return *reinterpret_cast<X*>(Code + index);
	}
};
