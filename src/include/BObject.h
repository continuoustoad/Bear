#pragma once
#include <BType.h>
#include <Refs.h>
#include <Exception.h>
#include <cinttypes>

class BObject
{
	TypeRef Type;
	std::uint16_t FieldCount;
	StrongRef Fields[];
public:
	const TypeRef &GetType() const noexcept { return Type; }
	StrongRef &Get(std::int32_t id)
	{
		if(id >= FieldCount || id < 0)
			throw Exception("VM/BObject/Get", "Field id out of range");
		return Fields[id];
	}

	StrongRef &Get(std::uint16_t id)
	{
		if(id >= FieldCount)
			throw Exception("VM/BObject/Get", "Field id out of range");
		return Fields[id];
	}
};

