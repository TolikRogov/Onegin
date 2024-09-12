#ifndef SORTING_INCLUDE
#define SORTING_INCLUDE

#include "../include/utilities.hpp"

enum SortingMod {
	FROM_LEFT_TO_RIGHT,
	FROM_RIGHT_TO_LEFT
};

OneginStatusCode LibraryQsort(Storage* storage, SortingMod mod);
int CompareStringLeftRight(const void* str1, const void* str2);
int CompareStringRightLeft(const void* str1, const void* str2);
int CustomStrcmpLeftRight(const char* string1, const char* string2);
int CustomStrcmpRightLeft(const String* const str1_inf, const String* const str2_inf);

#endif //SORTING_INCLUDE