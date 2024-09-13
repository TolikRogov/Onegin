#include "../include/Sorting.hpp"

void BubbleSort(void* array, size_t cnt, size_t size, compare_func_t comparator) {

	for (size_t i = 0; i < cnt; i++) {
		for (size_t j = 0; j < cnt - 1; j++) {

			void* el1 = ((String*)array + j * size);
			void* el2 = ((String*)array + (j + 1) * size);

			if (comparator(el1, el2) < 0) {
				void* tmp = el1;
				el1 = el2;
				el2 = tmp;
			}

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
			continue;
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
			continue;
		}

		if (tolower(*(str1_inf->cur_str + str1_pnt)) != tolower(*(str2_inf->cur_str + str2_pnt)))
			break;

		str1_pnt--;
		str2_pnt--;
	}

	return tolower(*(str1_inf->cur_str + str1_pnt)) - tolower(*(str2_inf->cur_str + str2_pnt));
}
