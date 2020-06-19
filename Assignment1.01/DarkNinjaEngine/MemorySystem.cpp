
#include "stdafx.h"

#include "MemorySystem.h"
#include "MemoryManager.h"
#include "FixedSizeAllocator.h"
using namespace customMalloc;

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	manager = MemoryManager::create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);

	
	//auto FSA_16= new(FixedSizeAllocator)(manager, FixedSizeManager_, 16, 100);

	//auto* FSA_32= new(FixedSizeAllocator)(manager, FixedSizeManager_, 32, 200);
	//auto* FSA_96= new(FixedSizeAllocator)(manager, FixedSizeManager_, 96, 200);
	//assert(manager);
	//std::cout << "size" << manager->totalSize << std::endl;
	//manager->listBlock();
	return true;
}
void* __alloc(size_t i_size)
{
	
	void* ptrToUser = nullptr;
	
	FixedSizeAllocator *ptrFSA= FixedSizeManager_.FindFixedSizeAllocator(i_size);

	if(ptrFSA)
	{
		
		ptrToUser=ptrFSA->FAlloc();
	}
	if (ptrToUser == nullptr)
	{
		 ptrToUser=manager->align_llAlloc(i_size);
	}
	return ptrToUser;
}
void __free(void* ptr)
{
	FixedSizeAllocator* ptrFSA = FixedSizeManager_.FindFixedSizeAllocatorFree(ptr);

	if (ptrFSA)
	{
		ptrFSA->FFree(ptr);
	}
	else 
	{
		
			manager->_free(ptr);
	}
}
void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager

	assert(manager);
	customMalloc::MemoryManager::collect();
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
}

