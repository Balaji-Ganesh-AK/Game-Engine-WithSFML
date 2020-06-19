#pragma once
#include "MemoryManager.h"



// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();
void* __alloc( size_t i_size);
void __free( void* i_ptr);
// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();
