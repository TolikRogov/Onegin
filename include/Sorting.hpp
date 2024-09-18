#ifndef SORTING_INCLUDE
#define SORTING_INCLUDE

#include "../include/utilities.hpp"

enum SortingMode {
	FROM_LEFT_TO_RIGHT,
	FROM_RIGHT_TO_LEFT
};

void BubbleSort(void* array, size_t cnt, size_t size, compare_func_t comparator);
void CustomQsort(void* array, size_t cnt, size_t size, compare_func_t comparator);

void SwapByByte(void* a, void* b, size_t size);

int CompareStringLeftRight(const void* str1, const void* str2);
int CompareStringRightLeft(const void* str1, const void* str2);
int CompareInt(const void* a, const void* b);

int CustomStrcmpLeftRight(const char* string1, const char* string2);
int CustomStrcmpRightLeft(const String* const str1_inf, const String* const str2_inf);

#endif //SORTING_INCLUDE
