#pragma once
#include <cstdlib>		//	for malloc and free
#include <iostream>	//	i hate iostream



//	my ancestors: "please don't do what i think you're going to do..."
//  ...
//  ........
//  ...............
// header file only *nuzlocke*

//  this class is so mf special, it makes me look normal
//  if u change ANYTHING it may get mad.
//  talk about tempermental

//  it tracks memory usage.
//  it tracks alllocations and deallocations.
//  i tried memory leak tracking but it breaks ahahhahah


//  notes for me later:
//  the map is what broke everything
//  for some reason it refuses to be initalized/used when extern/static/inline. which is rude

namespace MemoryManager {
    inline extern size_t totalMemory = 0;
    inline extern bool isMemorySpammingActive = false;

    enum class TextColour {
        DEFAULT,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
    };

    inline void SetTextColor(const TextColour color_) {
        switch (color_) {
        case TextColour::DEFAULT:
            std::cout << "\033[0m";
            break;
        case TextColour::BLACK:
            std::cout << "\033[30m";
            break;
        case TextColour::RED:
            std::cout << "\033[31m";
            break;
        case TextColour::GREEN:
            std::cout << "\033[32m";
            break;
        case TextColour::YELLOW:
            std::cout << "\033[33m";
            break;
        case TextColour::BLUE:
            std::cout << "\033[34m";
            break;
        case TextColour::MAGENTA:
            std::cout << "\033[35m";
            break;
        case TextColour::CYAN:
            std::cout << "\033[36m";
            break;
        case TextColour::WHITE:
            std::cout << "\033[37m";
            break;
        default:
            break;
        }
    }

    inline void ResetColour() {
        SetTextColor(TextColour::DEFAULT);
    }

}

void* operator new(const size_t size_) {
    using namespace MemoryManager;
    totalMemory += size_;
    void* ptr = std::malloc(size_);

    if(isMemorySpammingActive) {
    SetTextColor(TextColour::BLUE);
    std::cout << "Allocated ";
    SetTextColor(TextColour::GREEN);
    std::cout << size_;
    SetTextColor(TextColour::BLUE);
   	std::cout << " bytes. Total memory: ";
    SetTextColor(TextColour::GREEN);
    std::cout << totalMemory;
    SetTextColor(TextColour::BLUE);
    std::cout << " bytes.\n";
    ResetColour();

    }

    return ptr;
}

void operator delete(void* memory_, const size_t size_) {
    using namespace MemoryManager;
    totalMemory -= size_;
    std::free(memory_);

    if(isMemorySpammingActive) {
    SetTextColor(TextColour::RED);
    std::cout << "Deallocated ";
    SetTextColor(TextColour::GREEN);
    std::cout << size_;
    SetTextColor(TextColour::RED);
   	std::cout <<" bytes. Total memory: ";
    SetTextColor(TextColour::GREEN);
    std::cout << totalMemory;
    SetTextColor(TextColour::RED);
    std::cout << " bytes.\n";
    ResetColour();
    }

}