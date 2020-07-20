#pragma once
#include <Code.h>

class Runner
{
private:
	Chunk &Code;
	Byte *Instr;
public:
	Runner(Chunk &chunk) : Code(chunk)
	{
		Instr = chunk.Bytes;
	}
};
