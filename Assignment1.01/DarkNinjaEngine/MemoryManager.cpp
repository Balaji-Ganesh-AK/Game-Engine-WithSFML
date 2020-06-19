#include "stdafx.h"
#include "MemoryManager.h"
#include <iostream>


customMalloc::MemoryManager* manager = nullptr;

//#define heapSize 1024*1024


 Block* heapStart = nullptr;

/**
 * Current top. Updated on each allocation.
 */
 auto top = heapStart;
namespace customMalloc
{



	MemoryManager* MemoryManager::create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
	{
		MemoryManager* managerTest = reinterpret_cast<MemoryManager*>(malloc(sizeof MemoryManager));

		managerTest->startPtr = i_pHeapMemory;


		managerTest->totalSize = i_HeapMemorySize;
		managerTest->numberAllocations = 0;
		managerTest->offset = 0;
		managerTest->totalFreeMemory = 0;
		std::cout << "Virtual memory has been allocated" << managerTest << " " << managerTest->startPtr << std::endl;

		return managerTest;
	}


	//Fetch the address of the block
	Block* MemoryManager::getHeaderBlock(word_t* data) const
	{
		return reinterpret_cast<Block*>((char*)data + sizeof(std::declval<Block>().data) -
			sizeof(Block));
	}

	size_t MemoryManager::getEndPointer(Block* block)
	{

		return ((size_t)block + block->size + sizeof(Block));
	}

	// Free 
	bool MemoryManager::llFree(void* ptr)
	{
		auto* block = heapStart;



		while (block != nullptr)
		{
			if (block->data == ptr)
			{
				block->used = false;

				assert(block->data == ptr);
			//	totalFreeMemory = totalFreeMemory + block->size;
				return true;
			}
			block = block->next;
		}

		return false;

	}


	//First fit algo
	Block* MemoryManager::firstFit(size_t size, size_t alignment)
	{
		auto* block = heapStart;
		//listBlock();
		while (block != nullptr)
		{
			if (block->used == false && block->size >= size)
			{
				auto alignmentOffset = (size_t)block->data;
				 alignmentOffset = align(alignmentOffset, alignment,true);
			//	alignmentOffset = alignmentOffset - (size_t)block->data;

				if (block->size >= size + alignmentOffset)
					return block;

			}
			block = block->next;
		}

		return nullptr;
	}

	//Will add more search algo here;
	Block* MemoryManager::findBlock(const size_t size , size_t alignment)
	{

		return firstFit(size , alignment);
	}

	bool MemoryManager::is_free_block(size_t size)
	{
		Block* startBlock = heapStart;

		if (startBlock == nullptr)
		{
			return false;
		}
		if (startBlock->next == nullptr)
		{
			if (startBlock->used == false && startBlock->size <= size)
			{
				return true;
			}
		}
		if (startBlock->next == nullptr)
		{
			if (startBlock->used == false && startBlock->size <= size)
			{
				return true;
			}
			return false;
		}


		while (startBlock != nullptr)
		{
			std::cout << "yes" << startBlock->size << std::endl;
			if (startBlock->used == false)
			{
				if (startBlock->size <= size)
				{
					return true;
				}
				startBlock = startBlock->next;
			}
			else
				startBlock = startBlock->next;
		}

		return false;

	}

	//finds the largest block in the allocation list
	const Block* MemoryManager::findLargest()
	{
		auto startBlock = heapStart;
		if (startBlock->next == nullptr)
		{
			return startBlock;
		}
		auto largestBlock = startBlock;

		while (startBlock != nullptr)
		{
			// std::cout << "yes"<<startBlock->size<<std::endl;
			if (startBlock->used == true)
			{
				if (startBlock->size > largestBlock->size)
				{
					largestBlock = startBlock;
				}
				startBlock = startBlock->next;
			}
			else
				startBlock = startBlock->next;
		}

		return largestBlock;
	}

	//find the next address to allocate

	 //split the block into smaller blocks
	Block* MemoryManager::split(Block* i_block, size_t i_size, size_t i_alignment)
	{
		//testing
	if(i_size == 14)
	{
		std::cout << "h";
	}
		//Check if the block can be split 
		size_t checkSize = getEndPointer(i_block) - i_size;
		size_t alignmentOffset = align(checkSize , i_alignment,false);
		//alignmentOffset = alignmentOffset - checkSize;
		checkSize = checkSize - alignmentOffset - sizeof(Block);
		
	
		if ((size_t)(i_block->data)<checkSize)
		{
			Block* newBlock = (Block*)(checkSize);
			newBlock->size = i_size + alignmentOffset;
			newBlock->used = true;
			newBlock->data = ((word_t*)newBlock + sizeof(Block));
			newBlock->next = i_block->next;
			i_block->size =  checkSize- (size_t)i_block->data;
			i_block->next = newBlock;

			//std::cout << i_block->size;
			//listBlock();
			return newBlock;

		}
		else
			return nullptr;
	
	}

	//Free list allocator
	void* MemoryManager::llAlloc(size_t size)
	{
		return align_llAlloc(size);
	}

	//aligned malloc
	void* MemoryManager::align_llAlloc(size_t size, const size_t alignment)
	{
	 

		
		if (size == 648)
		{
			int i=1;
		}
			if (auto block = findBlock(size , (alignment)))
			{	
				
					
				
						if(auto Sblock = split(block, size, alignment))
							return Sblock->data;


					auto alignmentOffset = reinterpret_cast<size_t>(block->data);
					alignmentOffset = align(alignmentOffset, alignment,true);
				//	alignmentOffset = alignmentOffset - reinterpret_cast<size_t>(block->data);
					block->data = reinterpret_cast<word_t*>(reinterpret_cast<size_t>(block->data) + alignmentOffset);
					block->used = true;
					return block->data;
			}

		
	/*	if (totalSize < (offset + (size_t)sizeof(Block) + align(size, alignment)) && heapStart != nullptr)
		{
			Block* sBlock = heapStart;
			if (sBlock->used == false && sBlock->size >= size+32)
			{
				sBlock = split(sBlock, size, alignment);
				return sBlock->data;
			}
			
			return nullptr;
		}*/
		if (totalSize < offset+size+32)
		{
			return nullptr;
		}
			size_t currentAdr = offset + reinterpret_cast<size_t>(startPtr);
			//	std::cout << currentAdr<<"Total size"<<totalSize <<"Offset " << (offset + (size_t)sizeof(Block) + align(size, alignment)) << "*******************************************************************************" << std::endl;
			auto* block = (Block*)currentAdr;
			block->data = reinterpret_cast<word_t*>(currentAdr + sizeof(Block));

			//std::cout << "testsio" << align((size_t)block->data, alignment)<<std::endl;
			auto alignmentOffset = reinterpret_cast<size_t>(block->data);
			alignmentOffset = align(alignmentOffset, alignment);
			alignmentOffset = alignmentOffset - reinterpret_cast<size_t>(block->data);

			block->data = reinterpret_cast<word_t*>(reinterpret_cast<size_t>(block->data) + alignmentOffset);
			block->size = size + alignmentOffset;
			block->used = true;


			if (heapStart == nullptr) {

				heapStart = block;
			}
			if (top != nullptr)
			{

				while (top->next != nullptr)
				{

					top = top->next;
				}
				std::cout << "Size " << top->used << std::endl;
				top->next = block;
			}

			top = block;
			top->next = nullptr;

			offset = (sizeof(Block) + top->size + offset);
			//listBlock();
			assert((reinterpret_cast<uintptr_t>(top->data)& (alignment - 1)) == 0);

			bool success = Contains(top->data) && IsAllocated(top->data);
			//Testing
			if (!success)
			{
				listBlock();
				std::cout << IsAllocated(top->data);
				std::cout << "Block pointer " << (size_t)top << std::endl;
				std::cout << "Current adr" << currentAdr << std::endl;
				std::cout << "Size " << top->size << std::endl;
				std::cout << "Used " << top->used << std::endl;
				std::cout << "data " << top->data << std::endl;
				std::cout << "Next " << top->next << std::endl;
				

			}

			assert(success);

			return top->data;
		
		
		
	}


	//list all the blocks
	void MemoryManager::listBlock()
	{
		auto* startBlock = heapStart;
		if (startBlock == nullptr)
		{
			std::cout << "No block allocated!" << std::endl;
			return;
		}
		while (startBlock != nullptr)
		{

			std::cout << "             Listing all Blocks                 " << std::endl;
			std::cout << "================================================" << std::endl;
			std::cout << "Block size-> " << startBlock->size << std::endl;
			std::cout << "Block pointer-> " << (size_t)startBlock << std::endl;
			std::cout << "block start Pointer" << (size_t)startBlock->data << std::endl;
			std::cout << "end pointer-> " << getEndPointer(startBlock) << std::endl;
			std::cout << "Block next-> " << (size_t)startBlock->next << std::endl;
			std::cout << "Block used-> " << (size_t)startBlock->used << std::endl;
			//std::cout << "block pointer " << (size_t)getEndPointer(startBlock)<< std::endl;
			//std::cout << "block pointer+size+block-> " << (size_t)getHeaderBlock(startBlock->data) + startBlock->size + sizeof(Block) << std::endl;

			std::cout << "================================================" << std::endl;
			startBlock = startBlock->next;
		}
	}

	void MemoryManager::showFreeBlock()
	{
		auto* startBlock = heapStart;
		while (startBlock != nullptr)
		{
			if (startBlock->used == false)
			{
				std::cout << "             Free Blocks                        " << std::endl;
				std::cout << "================================================" << std::endl;
				std::cout << "Block size-> " << startBlock->size << std::endl;
				std::cout << "Block pointer-> " << startBlock->data << std::endl;
				std::cout << "Block next-> " << startBlock->next << std::endl;
				std::cout << "Block used-> " << startBlock->used << std::endl;
				std::cout << "================================================" << std::endl;

				startBlock = startBlock->next;
			}
			else
				startBlock = startBlock->next;
		}
	}

	bool MemoryManager::isContains(void* i_ptr, Block* block)
	{

		auto* startBlock = heapStart;
		while (startBlock != nullptr)
		{

			if (startBlock == block)
			{


			}
			startBlock = startBlock->next;
		}
		return false;
	}
	bool MemoryManager::isContains(void* i_ptr)
	{
		void* startPointer = startPtr;
		void* endPointer = static_cast<char*>(startPtr) + (totalSize);
		if (i_ptr >= startPointer && i_ptr <= endPointer)
		{
			return true;
		}
		return false;
	}

	bool MemoryManager::is_allocated(void* ptr)
	{
		auto* block = heapStart;
		//listBlock();
		//display();

		while (block != nullptr)
		{
			//std::cout <<"size? "<<block->size << "start " << (size_t)block << "Used? " << block->used << "next? " << (size_t)block->next << "End pointer?" << getEndPointer(block) <<"data " <<(size_t)block->data<< std::endl;



			if (block->used == true && block->next == nullptr)
			{

				void* startPointer = reinterpret_cast<void*>(block);
				void* end_pointer = reinterpret_cast<void*>(getEndPointer(block));
				//std::cout << " StartPointer  " << (size_t)startPointer << "  End pointer  " <<(size_t)end_pointer << " ptr? " << (size_t)block <<"  "<<(size_t)ptr<< std::endl;

				if (startPointer <= ptr && ptr <= end_pointer)
				{
					//std::cout << "Hi" << std::endl;
					return true;

				}
			}
			else if (block->used == true && block->next != nullptr)
			{

				void* startPointer = reinterpret_cast<void*>(block);
				void* end_pointer = reinterpret_cast<void*>(getEndPointer(block));
				//	std::cout << " StartPointer  " << (size_t)startPointer << "  End pointer  " << (size_t)end_pointer << " ptr? " << (size_t)block<< "  " << (size_t)ptr << std::endl;
				if (startPointer <= ptr && ptr <= end_pointer)
				{
					//std::cout << "Hi" << std::endl;
					return true;

				}

			}
			block = block->next;
		}

		return false;
	}

	void MemoryManager::showUsedMemory() const
	{
		std::cout << "Total memory ->" << totalSize << std::endl;
		std::cout << "Total Memory used->" << offset << std::endl;
		std::cout << "Memory available->" << totalFreeMemory + (totalSize - offset) << std::endl;
		//return offset;
	}

	void MemoryManager::insert(void* ptr)
	{


		if (Contains(ptr))
		{
			auto* startBlock = heapStart;
			if (startBlock == nullptr)
			{
				std::cout << "No block allocated!" << std::endl;
				return;
			}

			while (startBlock != nullptr)
			{

				if (startBlock->data == ptr)
				{
					struct FixedSizeList* new_node = reinterpret_cast<FixedSizeList*>(ptr);
					struct FixedSizeList* last_node = fixedSize_head;
					new_node->block = startBlock;
					new_node->next = nullptr;
					if (fixedSize_head == nullptr)
					{
						fixedSize_head = new_node;
						//std::cout << "Block Added" << std::endl;
						return;
					}
					while (last_node->next != nullptr)
					{
						last_node = last_node->next;
					}
					last_node->next = new_node;
					//std::cout << "Block Added" << std::endl;
					return;
				}
				startBlock = startBlock->next;
			}
		}

	}

	void MemoryManager::showFixedSizeLists()
	{
		struct FixedSizeList* temp = fixedSize_head;

		while (temp != nullptr)
		{
			std::cout << "           Fixed Size Allocated Blocks         " << std::endl;
			std::cout << "===============================================" << std::endl;
			std::cout << "Size: " << temp->block->size << std::endl;
			std::cout << "===============================================" << std::endl;
			temp = temp->next;
		}
	}




	size_t MemoryManager::get_minimum_to_leave()
	{
		return sizeof(Block);
	}


#ifdef unitTest


	void* MemoryManager::_alloc(size_t i_bytes)
	{
		return llAlloc(i_bytes);
	}

	void* MemoryManager::_alloc(size_t i_bytes, unsigned int i_alignment)
	{
		//TODO add more complex funtion here to check which allocation to use.

		return align_llAlloc(i_bytes, i_alignment);
	}

	bool MemoryManager::_free(void* i_ptr)
	{
		return llFree(i_ptr);
	}

	void MemoryManager::collect()
	{

		Block* temp = heapStart;
		Block* preBlock;
		if (temp->next == nullptr)
		{
			std::cout << "Failed";
			return;
		}
		while (temp->next != nullptr)
		{

			preBlock = temp;
			//std::cout << "before combine " << preBlock->used << std::endl;
			if (preBlock->used == false && preBlock->next->used == false)
			{

				preBlock->size = preBlock->size + temp->next->size;
				preBlock->next = temp->next->next;
				std::cout << "Combined Free Blocks" << preBlock->size << std::endl;
				temp = nullptr;
				temp = heapStart;
			}
			else {

				temp = temp->next;
			}
		}
	}

	size_t MemoryManager::getLargestFreeBlock()
	{

		auto* startBlock = heapStart;
		if (startBlock == nullptr)
		{
			return totalSize;
		}
		if (startBlock->next == nullptr)
		{
			return startBlock->size;
		}
		auto largestFreeBlock = startBlock;

		while (startBlock != nullptr)
		{
			// std::cout << "yes"<<startBlock->size<<std::endl;
			if (startBlock->used == false)
			{
				if (startBlock->size > largestFreeBlock->size)
				{
					largestFreeBlock = startBlock;
				}
				startBlock = startBlock->next;
			}
			else
				startBlock = startBlock->next;
		}

		return largestFreeBlock->size;

	}

	size_t MemoryManager::getTotalFreeMemory()
	{

		return totalFreeMemory;
	}

	bool MemoryManager::Contains(void* i_ptr)
	{
		return isContains(i_ptr);
	}

	bool MemoryManager::IsAllocated(void* i_ptr)
	{

		return is_allocated(i_ptr);
	}

	void MemoryManager::showfreeblocks()
	{
		showFreeBlock();
	}

	void MemoryManager::destroy()
	{
		Block* startBlock = heapStart;
		Block* temp = heapStart;
		while (temp != nullptr)
		{

			startBlock = temp;
			temp = temp->next;
			startBlock->next = nullptr;
			startBlock->data = nullptr;
			startBlock->size = 0;
			startBlock->used = false;
			startBlock = nullptr;

		}

		totalFreeMemory = totalSize;
		heapStart = nullptr;


	}
#endif




}

// Split function

//find the previous block

//auto* previousBlock = heapStart;
//Block* current = nullptr;
//while (previousBlock != nullptr)
//{
//
//	if (previousBlock == block)
//		break;
//	if (previousBlock->next == block)
//	{
//		current = previousBlock->next;
//		break;
//	}
//	previousBlock = previousBlock->next;
//}
//
////	std::cout << "Found? " << (size_t)block->next << std::endl;
//Block* tempadr = nullptr;
//void* nextptr = block->next;
//if (block->next != nullptr)
//{
//
//	tempadr = block->next;
//}
//else
//{
//	//	std::cout << "called" << std::endl;
//	nextptr = nullptr;
//	tempadr = nullptr;
//}
//
//
//const size_t temp = block->size;
//Block* smaller_block = nullptr;
//if (block == previousBlock)
//{
//	smaller_block = (previousBlock);
//}
//else
//smaller_block = (Block*)getEndPointer(previousBlock);
//
//
//
////std::cout << "addre" << (size_t)(smaller_block)<< std::endl;
//
//smaller_block->data = reinterpret_cast<word_t*>((size_t)(smaller_block)+sizeof(Block));
//
////std::cout << "addre" << (size_t)smaller_block->data << std::endl;
//
//
//
//auto alignmentOffset = reinterpret_cast<size_t>(smaller_block->data);
//alignmentOffset = align(alignmentOffset, alignment);
//alignmentOffset = alignmentOffset - reinterpret_cast<size_t>(smaller_block->data);
//
////std::cout << "aligned size" << alignmentOffset << std::endl;
//
//smaller_block->data = reinterpret_cast<word_t*>(reinterpret_cast<size_t>(smaller_block->data) + alignmentOffset);
//smaller_block->size = size + alignmentOffset;
//smaller_block->used = true;
//
//if (block != previousBlock)
//{
//	//	smaller_block = (previousBlock);
//	previousBlock->next = smaller_block;
//}
//
//
//
//auto* LargerBlock = (Block*)getEndPointer(smaller_block);
//smaller_block->next = LargerBlock;
//LargerBlock->data = (word_t*)(getEndPointer(smaller_block) + sizeof(Block) - alignmentOffset);
//
//LargerBlock->size = temp - smaller_block->size - alignmentOffset;
//if (alignmentOffset > 0)
//{
//	test = alignmentOffset + test;
//	std::cout << "alignmentOffset" << alignmentOffset << std::endl;
//}
//LargerBlock->next = (tempadr);
////LargerBlock->next = block->next;
//
//LargerBlock->used = false;
//
//if (getEndPointer(block) != getEndPointer(LargerBlock) && block != smaller_block)
//{
//
//	std::cout << "smaller block start" << (size_t)(smaller_block) << std::endl;
//	std::cout << "block start" << (size_t)block << std::endl;
//	std::cout << "block end" << getEndPointer(block) << std::endl;
//	std::cout << "LargerBlock end" << getEndPointer(LargerBlock) << std::endl;
//
//}
//
//assert((reinterpret_cast<uintptr_t>(smaller_block->data)& (alignment - 1)) == 0);
//assert(Contains(smaller_block->data));
//assert(Contains(LargerBlock->data));
//assert(is_allocated(smaller_block->data));
////	assert(is_allocated(LargerBlock->data));
//totalFreeMemory = totalFreeMemory - smaller_block->size;
//
//
//
//return smaller_block;
//
//
//
//
//
//

