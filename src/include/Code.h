#pragma once
#include <Common.h>

enum InstructionTypes
{
	DUPREF, DUPCOPY,
	NEW, ALLOC,
	DELETE, DEALLOC,
	NOP,
	LOADARG, LOADTYPE, LOADCONST
};

template<void *(*Allocator)(Size) = DefaultAllocator>
struct BaseChunk
{
	Size ChunkSize;
	Byte *Bytes;
	Chunk(Size size) : ChunkSize(size) {
		if(size == 0) throw Exception("Runner:ctor", "Cannot load an empty chunk."); // TODO: Allow empty chunks
		Bytes = Allocatord(size);
	}
};

using Chunk = BaseChunk<>; 
