#pragma once
#include <BType.h>
#include <Refs.h>
#include <cinttypes>

class BObject
{
	TypeRef Type;
	std::uint16_t FieldCount;
	StrongRef Fields[];
public:
	const TypeRef &GetType() const noexcept { return Type; }
	StrongRef &Get(int id) const {  }
};

