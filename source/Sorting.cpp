#include "../include/Sorting.hpp"

int CompareStringLeftRight(const void* str1, const void* str2) {

	const String* str1_inf = *(const String* const*)str1;
	const String* str2_inf = *(const String* const*)str2;

	return CustomStrcmpLeftRight(str1_inf->cur_str, str2_inf->cur_str);
}

int CompareStringRightLeft(const void* str1, const void* str2) {

	const String* str1_inf = *((const String* const*)str1);
	const String* str2_inf = *((const String* const*)str2);

	return CustomStrcmpRightLeft(str1_inf, str2_inf);
}

OneginStatusCode LibraryQsort(Storage* storage, SortingMod mod) {

	if (mod == FROM_LEFT_TO_RIGHT)
		qsort(storage->str_inf, storage->str_cnt, sizeof(String*), CompareStringLeftRight);
	else if (mod == FROM_RIGHT_TO_LEFT)
		qsort(storage->str_inf, storage->str_cnt, sizeof(String*), CompareStringRightLeft);
	else
		return ONEGIN_SORT_MOD_ERROR;

	return ONEGIN_NO_ERROR;
}

int CustomStrcmpLeftRight(const char* string1, const char* string2) {

	size_t str1_pnt = 0;
	size_t str2_pnt = 0;

	while ((*(string1 + str1_pnt) != '\0') && (*(string2 + str2_pnt) != '\0')) {
		if (!isalpha(*(string1 + str1_pnt))) {
			str1_pnt++;
			continue;
		}

		if (!isalpha(*(string2 + str2_pnt))) {
			str2_pnt++;
			continue;
		}

		if (tolower(*(string1 + str1_pnt)) != tolower(*(string2 + str2_pnt)))
			return tolower(*(string1 + str1_pnt)) - tolower(*(string2 + str2_pnt));

		str1_pnt++;
		str2_pnt++;
	}

	return 0;
}

int CustomStrcmpRightLeft(const String* const str1_inf, const String* const str2_inf) {

	size_t str1_pnt = str1_inf->cur_str_size - 1;
	size_t str2_pnt = str2_inf->cur_str_size - 1;

	while (str1_pnt != 0 && str2_pnt != 0) {
		if (!isalpha(*(str1_inf->cur_str + str1_pnt))) {
			str1_pnt--;
			continue;
		}

		if (!isalpha(*(str2_inf->cur_str + str2_pnt))) {
			str2_pnt--;
			continue;
		}

		if (tolower(*(str1_inf->cur_str + str1_pnt)) != tolower(*(str2_inf->cur_str + str2_pnt)))
			return tolower(*(str1_inf->cur_str + str1_pnt)) - tolower(*(str2_inf->cur_str + str2_pnt));

		str1_pnt--;
		str2_pnt--;
	}

	return 0;
}
