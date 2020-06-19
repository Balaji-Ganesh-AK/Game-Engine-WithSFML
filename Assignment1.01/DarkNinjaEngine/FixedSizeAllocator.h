#pragma once
#include "stdafx.h"


#include "MemoryManager.h"
#include <vector>

#include <iostream>
#include "HeaderFiles/Engine/Utility/IBitArray.h"

namespace customMalloc
{
	class FixedSizeManager
	{
	public:
		static FixedSizeManager* create();
		std::vector<FixedSizeAllocator* > fixed_size_allocators_;
	
		FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size);
		FixedSizeAllocator* FindFixedSizeAllocatorFree(void*ptr);
		
	};
	class FixedSizeAllocator 
	{
	public:
		FixedSizeAllocator(customMalloc::MemoryManager* i_pManager, FixedSizeManager &i_fixed_size_manager, size_t iBlockSize, size_t iNumOfBlocks);


		void* FAlloc();
		 void FFree(void* ptr) const;
		 bool is_free_available() const;
		const size_t blocksize_;
		bool is_allocated(void* ptr) const;
		bool is_contains(void *ptr) const;
	private:
		IBitArray Ibit;
		void* ptrPoolStart;
		const size_t num_blocks_;


		


	};
	
	


}
static customMalloc::FixedSizeManager FixedSizeManager_;

