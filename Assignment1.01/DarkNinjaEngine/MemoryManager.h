#pragma once

#include <assert.h>

#include <Windows.h>
#include <cstdint>
#define unitTest
using word_t = uint8_t;




 struct Block {

	//Size of the block
	size_t size;
	//Used ?
	bool used;

	//next block;
	Block *next;

	//pointer;
	uint8_t* data;
};
 struct FixedSizeList{
	Block *block;
	FixedSizeList*next;
};

// struct FixedSizeListtest {
//	FixedSizeAllocator *fixedptr;
//	FixedSizeList* next;
//};
//static FixedSizeListtest* fixedSizeTest_Head = nullptr;

static FixedSizeList* fixedSize_head = nullptr;

typedef uint16_t offset_t;
#define PTR_OFFSET_SZ sizeof(offset_t)
#define BLOCK_SIZE sizeof(Block*)
//can the block split?
inline bool canSplit(Block *block, size_t size)
{
	return ( (block-> size+(size_t)block->data ) > sizeof(block) )? true : false;
}

//alignment functions
inline size_t align(size_t size, size_t alignment,bool isForward)
{

	if (size % alignment == 0)
	{
		return 0;
	}
	if (isForward)
	{
		
		return alignment -( size % alignment);
	}
	else
	{
		return size % alignment;
	}
}
inline size_t align(size_t size, size_t alignment)
{
	return (((size)+((alignment)-1)) &~((alignment)-1));
}

inline size_t align(size_t n) {
	return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}



//returns the total size of the block
inline size_t getBlockSize(Block *block)
{
	return (sizeof(Block) + block->size);
}



namespace customMalloc
{

	class FixedSizeAllocator;
	class MemoryManager
	{
		
		
	public:
		
	//allocate the inital memory space 
		static  MemoryManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);


		//Free list allocator
		 void* llAlloc(size_t size);
		
		//alligned malloc
		void* align_llAlloc(size_t size, size_t alignment=4);
	
		
		//gets the start address of the block
		Block* getHeaderBlock(word_t* data) const;

		//gets the end pointer address of the block
		static size_t getEndPointer(Block* data);
		//Free function
		bool llFree(void *ptr);

		//First fit algorithum
		 Block *firstFit(size_t size, size_t alignment);
		//Find block 
		// Will add more search algo
		 Block *findBlock(const size_t size, size_t alignment);
		 //is free block available
		
		 
		//finds the largest block;
		static const  Block *findLargest();
		//split the free block into smaller blocks
		Block *split(Block *block, size_t size,size_t alignment);
		static bool is_free_block(size_t size);
		//list all the blocks
		 void listBlock();
		//lists all free blocks
		static void showFreeBlock();
		
		//Checks if the pointer is present in the heap
		 bool isContains(void * i_ptr, Block *block);
		 bool isContains(void * i_ptr);

		 bool is_allocated(void *ptr);
		void showUsedMemory() const;

		
		//LinkedList
		void insert(void*ptr);
		void showFixedSizeLists();

		//Linked list operations
		//insert
		
		
		static size_t get_minimum_to_leave();


		//override new and delete
		/* void* operator new(size_t size);

		void operator delete(void* ptr);*/
#ifdef unitTest
		 void* _alloc(size_t i_bytes);
		// allocation with alignment. returns a block of memory with a given alignment
		void* _alloc(size_t i_bytes, unsigned int i_alignment);

		// frees an allocation
		bool _free(void* i_ptr);

		// attempt to merge abutting blocks.
		static void collect();
		//Track allocated blocks
		
		// tells us the size of the largest free block
		size_t getLargestFreeBlock();
		// tells us how much total memory is available
		size_t getTotalFreeMemory();

		// tells us if a pointer is within this HeapManagers managed memory
		 bool Contains(void * i_ptr);
		// tells us if this pointer is an outstanding allocation from this block
		bool IsAllocated(void* i_ptr);

		// a debugging helper function to show us all the free blocks.
		void showfreeblocks();
		void destroy();

#endif
		
		size_t offset=0;
		size_t totalFreeMemory=0;
		void* startPtr = NULL;
		size_t numberAllocations = 0;
		size_t totalSize = 0;
		size_t used = 0;

		size_t test = 0;
	protected:
		
	};

	

	
}
extern customMalloc::MemoryManager* manager;

//static customMalloc::FixedSizeManager* fixed_size_manager;

 
