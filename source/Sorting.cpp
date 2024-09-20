#include "../include/Sorting.hpp"

void CustomQsort(void* array, size_t cnt, size_t size, compare_func_t comparator) {

	if ((char*)array < ((char*)array + (cnt - 1) * size)) {
		char* middle_index = Partition(array, cnt, size, comparator);
		CustomQsort(array, (size_t)((char*)middle_index - (char*)array) / size, size, comparator);
		CustomQsort(middle_index, (size_t)((char*)array + cnt * size - (char*)middle_index) / size, size, comparator);
	}

}

char* Partition(void* array, size_t cnt, size_t size, compare_func_t comparator) {

	char* middle_index = (char*)array;
	char* middle_value = ((char*)array + (cnt - 1) * size);

	for (char* j = (char*)array; j < ((char*)array + (cnt - 1) * size); j += size) {
		if (comparator(j, middle_value) <= 0) {
			SwapByByte(j, middle_index, size);
			middle_index += size;
		}
	}

	SwapByByte(middle_index, ((char*)array + (cnt - 1) * size), size);

	return middle_index;
}

void BubbleSort(void* array, size_t cnt, size_t size, compare_func_t comparator) {

	for (size_t i = 0; i < cnt - 1; i++) {
		for (size_t j = i + 1; j < cnt; j++) {
			if (comparator(((char*)array + i * size), ((char*)array + j * size)) > 0)
				SwapByByte(((char*)array + i * size), ((char*)array + j * size), size);
		}
	}

}

int CompareStringLeftRight(const void* str1, const void* str2) {

	const String* str1_inf = (const String*)str1;
	const String* str2_inf = (const String*)str2;

	return CustomStrcmpLeftRight(str1_inf->cur_str, str2_inf->cur_str);
}

int CompareStringRightLeft(const void* str1, const void* str2) {

	const String* str1_inf = (const String*)str1;
	const String* str2_inf = (const String*)str2;

	return CustomStrcmpRightLeft(str1_inf, str2_inf);
}

int CustomStrcmpLeftRight(const char* string1, const char* string2) {

	size_t str1_pnt = 0;
	size_t str2_pnt = 0;

	while ((*(string1 + str1_pnt) != '\0') && (*(string2 + str2_pnt) != '\0')) {

		if (!isalpha(*(string1 + str1_pnt)) || !isalpha(*(string2 + str2_pnt))) {
			while (!isalpha(*(string1 + str1_pnt)) && (*(string1 + str1_pnt)) != '\0')
				str1_pnt++;
			while (!isalpha(*(string2 + str2_pnt)) && (*(string2 + str2_pnt)) != '\0')
				str2_pnt++;
		}

		if (tolower(*(string1 + str1_pnt)) != tolower(*(string2 + str2_pnt)))
			break;

		str1_pnt++;
		str2_pnt++;
	}

	return tolower(*(string1 + str1_pnt)) - tolower(*(string2 + str2_pnt));
}

int CustomStrcmpRightLeft(const String* const str1_inf, const String* const str2_inf) {

	size_t str1_pnt = str1_inf->cur_str_size - 1;
	size_t str2_pnt = str2_inf->cur_str_size - 1;

	while (str1_pnt != 0 && str2_pnt != 0) {

		if (!isalpha(*(str1_inf->cur_str + str1_pnt)) || !isalpha(*(str2_inf->cur_str + str2_pnt))) {
			while (!isalpha(*(str1_inf->cur_str + str1_pnt)) && str1_pnt != 0)
				str1_pnt--;
			while (!isalpha(*(str2_inf->cur_str + str2_pnt)) && str2_pnt != 0)
				str2_pnt--;
		}

		if (tolower(*(str1_inf->cur_str + str1_pnt)) != tolower(*(str2_inf->cur_str + str2_pnt)))
			break;

		str1_pnt--;
		str2_pnt--;
	}

	return tolower(*(str1_inf->cur_str + str1_pnt)) - tolower(*(str2_inf->cur_str + str2_pnt));
}

void SwapByByte(void* a, void* b, size_t size) {

	for (size_t i = 0; i < size; i++) {
		char tmp = *((char*)a + i);
		*((char*)a + i) = *((char*)b + i);
		*((char*)b + i) = tmp;
	}

}
