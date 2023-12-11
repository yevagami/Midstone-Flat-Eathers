#pragma once
#include <cstdlib>		//	for malloc and free
#include <iostream>	//	i hate iostream



//	my ancestors: "please don't do what i think you're going to do..."
//	        ...

//  this class is so mf special, it makes me look normal
//  if u change ANYTHING it may get mad.
//  talk about tempermental

//  it tracks memory usage.
//  it tracks alllocations and deallocations.
//  i tried memory leak tracking but it breaks ahahhahah


//  notes for me later:
//  the map is what broke everything
//  for some reason it refuses to be initalized/used when extern/static/inline. which is rude

inline extern size_t totalMemory = 0;
inline extern bool isMemorySpammingActive = false;

enum class TextColor {
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

inline void SetTextColor(const TextColor color_) {
    switch (color_) {
    case TextColor::DEFAULT:
        std::cout << "\033[0m";
        break;
    case TextColor::BLACK:
        std::cout << "\033[30m";
        break;
    case TextColor::RED:
        std::cout << "\033[31m";
        break;
    case TextColor::GREEN:
        std::cout << "\033[32m";
        break;
    case TextColor::YELLOW:
        std::cout << "\033[33m";
        break;
    case TextColor::BLUE:
        std::cout << "\033[34m";
        break;
    case TextColor::MAGENTA:
        std::cout << "\033[35m";
        break;
    case TextColor::CYAN:
        std::cout << "\033[36m";
        break;
    case TextColor::WHITE:
        std::cout << "\033[37m";
        break;
    default:
        break;
    }
}

inline void ResetColor() {
    SetTextColor(TextColor::DEFAULT);
}

void* operator new(const size_t size_) {
    totalMemory += size_;
    void* ptr = std::malloc(size_);

    if(isMemorySpammingActive) {
    SetTextColor(TextColor::BLUE);
    std::cout << "Allocated " << size_ << " bytes. Total memory: ";
    SetTextColor(TextColor::MAGENTA);
    std::cout << totalMemory;
    std::cout << " bytes.\n";
    ResetColor();

    }

    return ptr;
}

void operator delete(void* memory_, const size_t size_) {
    totalMemory -= size_;
    std::free(memory_);

    if(isMemorySpammingActive) {
    SetTextColor(TextColor::RED);
    std::cout << "Deallocated " << size_ << " bytes. Total memory: ";
    SetTextColor(TextColor::MAGENTA);
    std::cout << totalMemory;
    std::cout << " bytes.\n";
    ResetColor();
    }

}