#pragma once
#include "MemoryManager.h"

namespace HeapManagerProxy
{
	customMalloc::MemoryManager* CreateHeapManager(void* i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	
	
	void* alloc(customMalloc::MemoryManager* i_pManager, size_t i_size);
	void* alloc(customMalloc::MemoryManager* i_pManager, size_t i_size, unsigned int i_alignment);
	//void* realloc(customMalloc::MemoryManager* i_pManager, void* i_ptr, size_t i_size);
	//void* realloc(customMalloc::MemoryManager* i_pManager, void* i_ptr, size_t i_size, unsigned int i_alignment);
	void Destroy(customMalloc::MemoryManager  * i_pManager);
	bool free(customMalloc::MemoryManager* i_pManager, void* i_ptr);
	void Collect(customMalloc::MemoryManager * i_pManager);
	//void Collect(customMalloc::MemoryManager* i_pManager);

	bool Contains(customMalloc::MemoryManager* i_pManager, void* i_ptr);
	bool IsAllocated(customMalloc::MemoryManager* i_pManager, void* i_ptr);

	//size_t getLargestFreeBlock(customMalloc::MemoryManager* i_pManager);
	//size_t getTotalFreeMemory(customMalloc::MemoryManager* i_pManager);

	void ShowFreeBlocks(customMalloc::MemoryManager* i_pManager);
	void ShowOutstandingAllocations(const customMalloc::MemoryManager* i_pManager);
	
	

	// frees an allocation
	void _free(void* i_ptr);


	// tells us the size of the largest free block
	size_t GetLargestFreeBlock(customMalloc::MemoryManager* i_pManager);
	// tells us how much total memory is available
	size_t GetTotalFreeMemory();

	
	

};