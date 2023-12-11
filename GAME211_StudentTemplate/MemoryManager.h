#pragma once
#include <cstdlib>		//	for malloc and free
#include <memory>
//#include <new>	//	for std::bad_alloc, but <memory> also covers that
#include <iostream>	//	i hate iostream
#include <unordered_map>	//	for the memory map (memory leak tracking)

//	my ancestors: "please don't do what i think you're going to do..."
//	fine... its not all in the header file.

class MemoryManager {
public:
	//	counts the number of currently allocated pointers
	static size_t allocationCount;
	//	counts the amount of total allocated memory
	static size_t totalAllocatedMemory;

	//	for memory leak detection. it maps all pointers to their current size
	static std::unordered_map<void*, size_t> memoryMap;

	~MemoryManager() {
		//	clean up any remaining allocated memory
		for(const auto& mapEntry : memoryMap) {
			free(mapEntry.first);
		}
	}

#pragma region Console Management Lite
	//	this method is for readability and so i can make complexish coloury things
	static void log(const char* action_, const size_t size_ = 0);

	//	these need to be static inline.
	//	a) because they're all in the header file (inline)
	//	b) because "new" and "delete" operator overrides are inately static and will
	//		be called from outside the class, therefore they have to "all be one package" in a sense
	inline static const char* blue = "\033[1;34m";
	inline static const char* cyan = "\033[1;36m";
	inline static const char* green = "\033[1;32m";
	inline static const char* purple = "\033[1;35m";
	inline static const char* pink = "\033[1;95m";
	inline static const char* yellow = "\033[1;33m";
	inline static const char* red = "\033[1;31m";
	inline static const char* resetColor = "\033[0m";
#pragma endregion
};

void* operator new(size_t size_);

void operator delete(void* memory_);

///	THE IMPORTANT PART... that's broken

//	the global versions (to override ALL new and deletes...)
//	these break everything :D
//void* operator new(size_t size_) noexcept;
//void operator delete(void* memory_) noexcept;