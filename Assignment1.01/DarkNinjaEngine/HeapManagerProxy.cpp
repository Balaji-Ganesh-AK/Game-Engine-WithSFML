#include "stdafx.h"
#include "HeapManagerProxy.h"
#include "MemoryManager.h"

namespace  HeapManagerProxy
{
	customMalloc::MemoryManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
		return customMalloc::MemoryManager::create(i_pMemory, i_sizeMemory, i_numDescriptors);
	}

	void Destroy(customMalloc::MemoryManager  * i_pManager)
	{
		assert(i_pManager);

		i_pManager->destroy();
	}



	void * alloc(customMalloc::MemoryManager * i_pManager, size_t i_size)
	{
		assert(i_pManager);
		return i_pManager->_alloc(i_size);
	}

	void * alloc(customMalloc::MemoryManager * i_pManager, size_t i_size, unsigned int i_alignment)
	{
		assert(i_pManager);

		return i_pManager->_alloc(i_size, i_alignment);
	}

	bool free(customMalloc::MemoryManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		return i_pManager->_free(i_ptr);
	}
	void Collect(customMalloc::MemoryManager * i_pManager)
	{
		assert(i_pManager);

		i_pManager->collect();
	}



	bool Contains(customMalloc::MemoryManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);

		return i_pManager->Contains(i_ptr);

	}

	bool IsAllocated(customMalloc::MemoryManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		//std::cout << "IsAllocated?" << i_pManager->IsAllocated(i_ptr) << std::endl;
		return i_pManager->IsAllocated(i_ptr);
	}

	size_t GetLargestFreeBlock(customMalloc::MemoryManager * i_pManager)
	{
		assert(i_pManager);

		return i_pManager->getLargestFreeBlock();
	}

	size_t GetTotalFreeMemory(customMalloc::MemoryManager * i_pManager)
	{
		assert(i_pManager);

		return i_pManager->getLargestFreeBlock();
	}

	void ShowFreeBlocks(customMalloc::MemoryManager * i_pManager)
	{
		assert(i_pManager);

		i_pManager->showfreeblocks();
	}

	void ShowOutstandingAllocations(const customMalloc::MemoryManager * i_pManager)
	{
		assert(i_pManager);

#ifdef __TRACK_ALLOCATIONS
		i_pManager->ShowOutstandingAllocations();
#else
//		printf("HeapManager compiled without __TRACK_ALLOCATIONS defined.\n");
#endif

	}

} // namespace HeapManagerProxy