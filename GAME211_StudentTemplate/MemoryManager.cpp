#include "MemoryManager.h"

size_t MemoryManager::allocationCount = 0;
size_t MemoryManager::totalAllocatedMemory = 0;
std::unordered_map<void*, size_t> MemoryManager::memoryMap;

void* MemoryManager::operator new(size_t size_) {
	//	memory allocation
	void* memory = malloc(size_);

	//	tracking and management
	if (memory) {
		allocationCount++;
		totalAllocatedMemory += size_;
		memoryMap[memory] = size_;
		log("Allocated", size_);
	}
	else {
		//	failed memory allocation
		throw std::bad_alloc();
	}

	return memory;
}

void MemoryManager::operator delete(void* memory_) noexcept {
	//	if theres memory
	if (memory_) {
		//	find the spot in the map the memory is associated to (tracking and management)
		if (const auto it = memoryMap.find(memory_); it != memoryMap.end()) {
			allocationCount--;
			totalAllocatedMemory -= it->second;
			log("Deallocated", it->second);
			memoryMap.erase(it);

			//	the memory deallocation
			free(memory_);
			//

		}
	}
}

void MemoryManager::log(const char* action_, const size_t size_) {
	if (action_ == "Allocated") {
		std::cout << blue << action_ << " " << cyan << size_ << blue << " bytes. "
			<< "Total Allocations: " << cyan << allocationCount << blue
			<< ", Total allocated memory: " << cyan << totalAllocatedMemory << blue << " bytes."
			<< resetColor << std::endl;
	}
	else if (action_ == "Deallocated") {
		std::cout << red << action_ << " " << pink << size_ << " bytes. "
			<< "Total Allocations: " << pink << allocationCount << red
			<< resetColor << std::endl;
	}
}

//void* operator new(size_t size_) noexcept {
//	return MemoryManager::operator new(size_);
//}
//void operator delete(void* memory_) noexcept {
//	MemoryManager::operator delete(memory_);
//}
