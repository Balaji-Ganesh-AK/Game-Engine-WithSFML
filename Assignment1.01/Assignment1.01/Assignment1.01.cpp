//// Assignment1.01.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
//
//#include "Assignment1.01.h"
//#include "GLib.h"
//#include "DarkNinjaEngine.h"
//#include "stdafx.h"
//
//
//
//#include <Windows.h>
//
//#include "MemorySystem.h"
//
//#include <assert.h>
//#include <algorithm>
//#include <vector>
//
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#endif // _DEBUG
//#include <DarkNinjaEngine.cpp>
//#define split
//#define list
////#define MEMORYTEST
////#define monsterChase
////#define UnitTestFinal
//
//
//
//using namespace Engine;
//using namespace vec2;
//using namespace customMalloc;
//
//int count = 0;
//char* name = reinterpret_cast<char*>(malloc(sizeof(char)));
//
//Point2D up(0, 1),
//right(1, 0),
//down(0, -1),
//left(-1,0),
//playerPosition(0, 0);
//
//
//
//
////void checkMonsterCollision(monsterNode_t* current)
////{
////	monsterNode_t* temp;
////	temp = current->next;
////
////	while (temp != nullptr)
////	{
////		if (temp->monsterLocation == playerPosition)
////		{
////			std::cout << "Player DEAD!! Game Over!";
////			exit(0);
////		}
////		temp = temp->next;
////	}
////}
//
//#ifdef monsterChase
//void movePlayer(char keyPress, monsterNodeTest_t* current, int a, Entity& actor, EntityManager &EntityManager_)
//{
//	switch (keyPress)
//	{
//	case 'A':
//	case 'a':
//		playerPosition - right;
//		actor.GetComponent<Position>()->setPosition(left);
//
//
//		print(current);
//		break;
//	case 'D':
//	case 'd':
//		playerPosition + right;
//		actor.GetComponent<Position>()->setPosition(right);
//
//		print(current);
//		break;
//	case 'W':
//	case 'w':
//		playerPosition + up;
//		actor.GetComponent<Position>()->setPosition(up);
//
//		print(current);
//		break;
//	case 'S':
//	case 's':
//		playerPosition - up;
//		actor.GetComponent<Position>()->setPosition(down);
//
//		print(current);
//		break;
//	case 'q':
//	case 'Q':
//		exit(0);
//
//	case 'E':
//	case 'e':
//		add(current, EntityManager_);
//		print(current);
//		break;
//	case 'R':
//	case 'r':
//		current = deleteMonster(current);
//		print(current);
//		break;
//	default:;
//	}
//}
//#endif
//
//
//void Point2D_UnitTest()
//{
//	Point2D P1(20.0f, 20.0f);
//	Point2D P2(10.0f, 10.0f);
//
//	Point2D P3 = P1 + P2;
//	P3 = P1 - P2;
//
//	Point2D P4 = P1 * 0.5f;
//
//	Point2D P5 = P1 / 2.0f;
//
//	Point2D P6 = -P4;
//
//	P6 *= 2.0f;
//	P5 /= 4.0f;
//
//	P2 += P1;
//	P3 -= P1;
//
//	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;
//
//	bool bArentEqual = P6 != P4;
//}
//
//#ifdef  UnitTestFinal
//
//
//
//bool MemorySystem_UnitTest();
//
//int main(int i_arg, char**)
//{
//	const size_t 		sizeHeap = 1024 * 1024;
//
//	// you may not need this if you don't use a descriptor pool
//	const unsigned int 	numDescriptors = 2048;
//
//	// Allocate memory for my test heap.
//	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//	assert(pHeapMemory);
//
//	// Create your HeapManager and FixedSizeAllocators.
//	 InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
//
//
//	bool success = MemorySystem_UnitTest();
//	assert(success);
//
//	// Clean up your Memory System (HeapManager and FixedSizeAllocators)
//	DestroyMemorySystem();
//
//	HeapFree(GetProcessHeap(), 0, pHeapMemory);
//
//	// in a Debug build make sure we didn't leak any memory.
//#if defined(_DEBUG)
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//
//	return 0;
//}
//
//bool MemorySystem_UnitTest()
//{
//	const size_t maxAllocations = 10 * 1024;
//	std::vector<void*> AllocatedAddresses;
//
//	long	numAllocs = 0;
//	long	numFrees = 0;
//	long	numCollects = 0;
//
//	size_t totalAllocated = 0;
//
//	// reserve space in AllocatedAddresses for the maximum number of allocation attempts
//	// prevents new returning null when std::vector expands the underlying array
//	AllocatedAddresses.reserve(10 * 1024);
//
//	// allocate memory of random sizes up to 1024 bytes from the heap manager
//	// until it runs out of memory
//	do
//	{
//		const size_t		maxTestAllocationSize = 1024;
//
//		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));
//
//	//void* pPtr = malloc(sizeAlloc);
//
//		void* pPtr = __alloc(sizeAlloc);
//
//		// if allocation failed see if garbage collecting will create a large enough block
//		if (pPtr == nullptr)
//		{
//			Collect();
//
//			pPtr = __alloc(sizeAlloc);
//
//
//			// if not we're done. go on to cleanup phase of test
//			if (pPtr == nullptr)
//				break;
//		}
//
//		AllocatedAddresses.push_back(pPtr);
//		numAllocs++;
//
//		totalAllocated += sizeAlloc;
//
//		// randomly free and/or garbage collect during allocation phase
//		const unsigned int freeAboutEvery = 0x07;
//		const unsigned int garbageCollectAboutEvery = 0x07;
//
//		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
//		{
//			void* pPtrToFree = AllocatedAddresses.back();
//			AllocatedAddresses.pop_back();
//
//			//free(pPtrToFree);
//			__free(pPtrToFree);
//			numFrees++;
//		}
//		else if ((rand() % garbageCollectAboutEvery) == 0)
//		{
//			Collect();
//
//			numCollects++;
//		}
//
//	} while (numAllocs < maxAllocations);
//
//	// now free those blocks in a random order
//	if (!AllocatedAddresses.empty())
//	{
//		// randomize the addresses
//		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());
//
//		// return them back to the heap manager
//		while (!AllocatedAddresses.empty())
//		{
//			void* pPtrToFree = AllocatedAddresses.back();
//			AllocatedAddresses.pop_back();
//
//			//delete[] pPtrToFree;
//			__free(pPtrToFree);
//		}
//
//		// do garbage collection
//		Collect();
//	/*	 our heap should be one single block, all the memory it started with
//
//		 do a large test allocation to see if garbage collection worked*/
//	//	void* pPtr = malloc(totalAllocated / 2);
//		//void* pPtr = __alloc(totalAllocated / 2);
//
//		//if (pPtr)
//		//{
//		//	//free(pPtr);
//		//	__free(pPtr);
//		//}
//		//else
//		//{
//		//	// something failed
//		//	return true;
//		//}
//	}
//		else
//		{
//		return false;
//		}
//
//	// this new [] / delete [] pair should run through your allocator
//	/*char* pNewTest = new char[1024];
//
//	delete[] pNewTest;*/
//
//	// we succeeded
//	std::cout << "Passed!";
//	return true;
//}
//#endif //  UnitTestFinal
//
//
//
//#ifdef monsterChase
//	int main()
//	{
//	{
//
//		const size_t heapSize = 1024 * 1024;
//		const unsigned int nDescriptors = 1024;
//		void* block = HeapAlloc(GetProcessHeap(), 0, heapSize);
//		manager = MemoryManager::create(block, heapSize, nDescriptors);
//		EntityManager EntityManager_;
//		DarkNinjaEngine Dark;
//		Dark.Init();
//		{
//			//Main class;
//			Components Update(&EntityManager_);
//
//			//testing
//			Entity* MainPlayer = new Entity("Balaji", EntityManager_);
//			MainPlayer->AttachComponent(new Position(10, 10));
//			Entity* Monster = new Entity("Monster", EntityManager_);
//			Monster->AttachComponent(new AI);
//			Monster->GetComponent<AI>()->PositionAI(10, 10);
//
//
//			char keyPress;
//
//			auto* headPointer = reinterpret_cast<monsterNodeTest*>(malloc(sizeof(monsterNodeTest_t)));
//			headPointer->next = nullptr;
//			auto* currentPointer = headPointer;
//
//
//
//
//
//
//			//TODO::add a current if only the number of monster is more than 1
//			int a;
//			std::cout << "Enter the number of monsters : ";
//
//			std::cin >> a;
//
//
//			for (int i = 0; i < a; i++)
//			{
//
//				//head = addMonster(head);
//				headPointer = add(headPointer, EntityManager_);
//			}
//			std::cout << "Enter the name of the player :";
//			std::cin >> name;
//
//			while (true)
//			{
//				std::cout << "Press A to move left, D to move right, W to move up, S to move down, Q to quit , E to add a new monster, R to delete a monster randomly";
//				std::cin >> keyPress;
//				movePlayer(keyPress, headPointer, a, *MainPlayer, EntityManager_);
//
//
//				Update.Update();
//				//print(headPointer);
//				std::cout << "Player " << MainPlayer->get_name() << MainPlayer->GetComponent<Position>()->getPosition() << std::endl;
//
//			}
//			Dark.end();
//			_CrtDumpMemoryLeaks();
//
//		}
//	}
//}
//monsterNodeTest_t* add(monsterNodeTest_t* headPointer, EntityManager& EntityManager_)
//{
//
//	count++;
//	monsterNodeTest_t* current = headPointer;
//	//todo change it to malloc
//	char* nameTemp = reinterpret_cast<char*>(malloc(sizeof(char)));
//	while (current->next != nullptr)
//	{
//		current = current->next;
//	}
//#pragma warning(disable:6011)
//	std::cout << "Enter name of the monster " << count << " : ";
//	std::cin >> nameTemp;
//	auto* tempTest = new monsterNodeTest_t;
//	tempTest->monster = new Entity(nameTemp, EntityManager_);
//
//	//Attaching AI component
//	tempTest->monster->AttachComponent(new AI());
//	//Setting the AI position
//	tempTest->monster->GetComponent<AI>()->PositionAI(rand() % 10, rand() % 10);
//
//
//
//	current->next = tempTest;
//
//	tempTest->next = nullptr;
//
//	return headPointer;
//}
//
//monsterNodeTest_t* deleteMonster(monsterNodeTest_t* headPointer)
//{
//	monsterNodeTest_t* temp = headPointer;
//	while (temp->next->next != nullptr)
//	{
//		temp = temp->next;
//	}
//	monsterNodeTest_t* current = temp->next->next;
//	delete(current);
//	temp->next = NULL;
//	return headPointer;
//}
//
//void print(monsterNodeTest_t* current)
//{
//	monsterNodeTest_t* temp = current->next;
//	if (current->next == nullptr)
//	{
//		std::cout << "empty";
//	}
//	while (temp != nullptr)
//	{
//		std::cout << "Monster " << temp->monster->get_name() << " is at " << temp->monster->GetComponent<AI>()->getPositionAI() << std::endl;
//		temp = temp->next;
//	}
//}
//
//#endif
//
////_CrtDumpMemoryLeaks();
//
//void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
//GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
//
//void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
//{
//#ifdef _DEBUG
//	const size_t	lenBuffer = 65;
//	char			Buffer[lenBuffer];
//
//	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
//	OutputDebugStringA(Buffer);
//#endif // __DEBUG
//}
//
////game code
//
//
//int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
//{
//	//EntityManager EntityManager_;
//	// IMPORTANT: first we need to initialize GLib
//	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
//
//
//	if (bSuccess)
//	{
//		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
//		//GLib::SetKeyStateChangeCallback(TestKeyCallback);
//		GLib::SetKeyStateChangeCallback(TestKeyCallback);
//
//		// Create a couple of sprites using our own helper routine CreateSprite
//		GLib::Sprites::Sprite * pGoodGuy = CreateSprite("data\\GoodGuy.dds");
//		GLib::Sprites::Sprite * pBadGuy = CreateSprite("data\\BadGuy.dds");
//
//		bool bQuit = false;
//
//
//
//		do
//		{
//			// IMPORTANT: We need to let GLib do it's thing.
//			GLib::Service(bQuit);
//
//			if (!bQuit)
//			{
//				// IMPORTANT: Tell GLib that we want to start rendering
//				GLib::BeginRendering();
//				// Tell GLib that we want to render some sprites
//				GLib::Sprites::BeginRendering();
//
//				if (pGoodGuy)
//				{
//					static float			moveDist = .01f;
//					static float			moveDir = moveDist;
//
//					static GLib::Point2D	Offset = { -180.0f, -100.0f };
//
//					if (Offset.x < -220.0f)
//						moveDir = moveDist;
//					else if (Offset.x > -140.0f)
//						moveDir = -moveDist;
//
//					Offset.x += moveDir;
//
//					// Tell GLib to render this sprite at our calculated location
//					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
//				}
//				if (pBadGuy)
//				{
//					static float			moveDist = .02f;
//					static float			moveDir = -moveDist;
//
//					static GLib::Point2D	Offset = { 180.0f, -100.0f };
//
//					if (Offset.x > 200.0f)
//						moveDir = -moveDist;
//					else if (Offset.x < 160.0f)
//						moveDir = moveDist;
//
//					Offset.x += moveDir;
//
//					// Tell GLib to render this sprite at our calculated location
//					GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
//				}
//
//				// Tell GLib we're done rendering sprites
//				GLib::Sprites::EndRendering();
//				// IMPORTANT: Tell GLib we're done rendering
//				GLib::EndRendering();
//			}
//		} while (bQuit == false);
//
//		if (pGoodGuy)
//			GLib::Sprites::Release(pGoodGuy);
//		if (pBadGuy)
//			GLib::Sprites::Release(pBadGuy);
//
//		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
//		GLib::Shutdown();
//	}
//
//#if defined _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//
//}
//
//GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
//{
//	assert(i_pFilename);
//
//	size_t sizeTextureFile = 0;
//
//	// Load the source file (texture data)
//	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);
//
//	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
//	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;
//
//	// exit if something didn't work
//	// probably need some debug logging in here!!!!
//	if (pTextureFile)
//		delete[] pTextureFile;
//
//	if (pTexture == nullptr)
//		return NULL;
//
//	unsigned int width = 0;
//	unsigned int height = 0;
//	unsigned int depth = 0;
//
//	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
//	bool result = GLib::GetDimensions(pTexture, width, height, depth);
//	assert(result == true);
//	assert((width > 0) && (height > 0));
//
//	// Define the sprite edges
//	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
//	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
//	GLib::RGBA							Color = { 255, 255, 255, 255 };
//
//	// Create the sprite
//	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
//	if (pSprite == nullptr)
//	{
//		GLib::Release(pTexture);
//		return nullptr;
//	}
//
//	// Bind the texture to sprite
//	GLib::Sprites::SetTexture(*pSprite, *pTexture);
//
//	return pSprite;
//}
//
//void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
//{
//	assert(i_pFilename != NULL);
//
//	FILE * pFile = NULL;
//
//	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
//	if (fopenError != 0)
//		return NULL;
//
//	assert(pFile != NULL);
//
//	int FileIOError = fseek(pFile, 0, SEEK_END);
//	assert(FileIOError == 0);
//
//	long FileSize = ftell(pFile);
//	assert(FileSize >= 0);
//
//	FileIOError = fseek(pFile, 0, SEEK_SET);
//	assert(FileIOError == 0);
//
//	uint8_t * pBuffer = new uint8_t[FileSize];
//	assert(pBuffer);
//
//	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
//	assert(FileRead == FileSize);
//
//	fclose(pFile);
//
//	o_sizeFile = FileSize;
//
//	return pBuffer;
//}
///*
//struct Counters
//{
//	long		m_strongCount;
//	long		m_weakCount;
//
//	Counters(long i_strongCount = 0, long i_weakCount = 0) :
//		m_strongCount(i_strongCount),
//		m_weakCount(i_weakCount)
//	{
//
//	}
//};
//
//template<typename T>
//class StrongPointer
//{
//public:
//	StrongPointer(T * i_ptr = NULL);
//	~StrongPointer();
//
//	StrongPointer(const StrongPointer & i_other);
//	StrongPointer &operator=(const StrongPointer & i_other);
//
//	T * operator->();
//	T & operator*();
//
//	operator bool() const;
//
//	bool operator==(const StrongPointer & i_other) const;
//};
//
//template<typename T>
//class WeakPointer
//{
//public:
//	WeakPointer(T * i_ptr = NULL);
//
//	WeakPointer(const WeakPointer & i_other);
//	WeakPointer &operator=(const WeakPointer & i_other);
//
//	StrongPointer<T> Acquire() const;
//
//	bool IsValid() const { return m_pObject != nullptr; }
//	operator bool() const { return IsValid();  }
//
//	T * operator->();
//	T & operator*();
//
//
//private:
//	T *			m_pObject;
//	Counters *	m_pCounters;
//};
//
//class UniquePointer
//{
//public:
//	UniquePointer(T * i_ptr = NULL);
//
//	UniquePointer(const UniquePointer & i_other);
//	UniquePointer &operator=(const UniquePointer & i_other);
//
//	bool IsValid() const { return m_pObject != nullptr; }
//	operator bool() const { return IsValid(); }
//
//	T * operator->();
//	T & operator*();
//
//private:
//	T *			m_pObject;
//};
//class Vector3
//{
//}
//
//class GameObject
//{
//
//public:
//	Vector3 GetPosition();
//};
//
//struct Renderable
//{
//	WeakPointer<GameObject> m_pObject;
//	GLib::Sprite *			m_pSprite;
//};
//
//void Draw( Renderable & i_Renderable)
//{
//	StrongPointer<GameObject> MyObj = i_Renderable.m_pObject.Acquire();
//
//	if (MyObj)
//	{
//		// if StrongPointer is valid draw it
//		GLib::Sprites::RenderSprite(*i_Renderable.m_pSprite, MyObj->GetPosition(), 0.0f);
//	}
//	else
//	{
//		// Need to destroy this Renderable since the GameObject has been released
//	}
//}
//
//void Test()
//{
//	// Ptr1 is the owner of the new GameObject
//	UniquePointer<GameObject> Ptr1(new GameObject("Joe"));
//
//	// Now Ptr2 is the owner and Ptr1 points to NULL
//	UniquePointer<GameObject> Ptr2 = Ptr1;
//
//	// Now Ptr1 is the owner and Ptr2 points to NULL
//	Ptr1 = Ptr2;
//}
//*/
