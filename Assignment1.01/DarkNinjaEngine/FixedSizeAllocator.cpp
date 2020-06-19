#include "stdafx.h"
#include "FixedSizeAllocator.h"
#include <iostream>

namespace customMalloc
{


	FixedSizeManager* FixedSizeManager::create()
	{
	//	FixedSizeManager* ptrFSA = new(FixedSizeManager)();
	FixedSizeManager* ptrFSA = reinterpret_cast<FixedSizeManager*>(malloc(sizeof (FixedSizeManager)));
		assert(ptrFSA);
		return ptrFSA;
	}

	FixedSizeAllocator* FixedSizeManager::FindFixedSizeAllocator(size_t i_size)
	{
		for (int i=0;i< fixed_size_allocators_.size();i++)
		{
			if (fixed_size_allocators_[i]->blocksize_ >= i_size)
			{
				
				if(fixed_size_allocators_[i]->is_free_available())
				{
					
					return fixed_size_allocators_[i];
				}
			}
		}
		return nullptr;
	}

	FixedSizeAllocator* FixedSizeManager::FindFixedSizeAllocatorFree(void* ptr)
	{
		for (int i = 0; i < fixed_size_allocators_.size(); i++)
		{
			if (fixed_size_allocators_[i]->is_allocated(ptr))
			{
				
					return fixed_size_allocators_[i];
			}
		}
		return nullptr;
	}

	FixedSizeAllocator::FixedSizeAllocator(customMalloc::MemoryManager* i_pManager, FixedSizeManager &i_fixed_size_manager, size_t iBlockSize,
		size_t iNumOfBlocks) :
		blocksize_(iBlockSize),
		Ibit(iNumOfBlocks),
		ptrPoolStart(reinterpret_cast<void*>(i_pManager->align_llAlloc(iBlockSize* iNumOfBlocks))),
		num_blocks_(iNumOfBlocks)
		
	{
		
		Ibit.set_all();
		i_fixed_size_manager.fixed_size_allocators_.push_back(this);
		std::cout << "Problem here?";
	}

	void* FixedSizeAllocator::FAlloc() 
	{
	
		const int index = Ibit.find_first_set_bit();
		
		if(Ibit.is_bit_set(index))
		{
			Ibit.clear_bit(index);
			return (reinterpret_cast<void*>((reinterpret_cast<size_t>(ptrPoolStart )+ (index * blocksize_))));
		}
		return nullptr;
	}

	void FixedSizeAllocator::FFree(void* ptr) const
	{
		if(is_allocated(ptr))
		{
			size_t index = reinterpret_cast<size_t>(ptr)-reinterpret_cast<size_t>(ptrPoolStart);
			index = index / blocksize_;
			Ibit.set_bit(index);
			std::cout << "BlockFreed" << std::endl;
		}
	}

	bool FixedSizeAllocator::is_free_available() const
	{
		return	!Ibit.is_all_bit_clear();
		
	}

	bool FixedSizeAllocator::is_allocated(void* ptr) const
	{
		if(is_contains(ptr))
		{
			size_t index = reinterpret_cast<size_t>(ptr) - reinterpret_cast<size_t>(ptrPoolStart);
			
			index = index / blocksize_;
			return !(Ibit.is_bit_set(index));
		}
		return false;
	}

	bool FixedSizeAllocator::is_contains(void* ptr) const
	{
		void* startptr = ptrPoolStart;
		void* endptr = static_cast<char*>(ptrPoolStart )+ (num_blocks_ * blocksize_);
		if(ptr>= startptr && ptr<=endptr)
		{
			return true;
		}
		return false;
	}
}


