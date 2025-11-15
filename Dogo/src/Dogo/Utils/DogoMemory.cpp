#include "dgpch.h"
#include "DogoMemory.h"
void* operator new(size_t size)
{
	Dogo::MemoryMetrics.TotalAllocated += uint32_t(size);
	//DG_TRACE("Allocating: %zu", size);
	return malloc(size);
}
void operator delete(void* memory, size_t size)
{
	Dogo::MemoryMetrics.TotalFreed += uint32_t(size);
	//DG_TRACE("Deallocating: %zu", size);
	free(memory);
}

namespace Dogo
{
	uint32_t MemoryUsage::TotalAllocated = 0;
	uint32_t MemoryUsage::TotalFreed = 0;
}