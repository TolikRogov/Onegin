#include "../include/Sorting.hpp"

void CustomQsort(void* array, size_t cnt, size_t size, compare_func_t comparator) {



// 	size_t i = 0;
// 	size_t j = cnt - 1;
//
// 	char* middle = ((char*)array + (cnt / 2) * size);
//
// 	fprintf(stderr, "NEW SORT START\n");
// 	fprintf(stderr, "cnt = %zu\n", cnt);
// 	fprintf(stderr, "array: ");
// 	for (size_t k = 0; k < cnt; k++) {
// 		fprintf(stderr, "%d ", *((char*)array + k * size));
// 	}
// 	fprintf(stderr, "\n");
// 	fprintf(stderr, "i = %zu, ", i);
// 	fprintf(stderr, "left = %d\n", *((char*)array + i * size));
// 	fprintf(stderr, "j = %zu, ", j);
// 	fprintf(stderr, "right = %d\n", *((char*)array + j * size));
// 	fprintf(stderr, "middle = %d\n", *middle);
// 	fprintf(stderr, "\n");
//
// 	do {
// 		// fprintf(stderr, "For left elements\n");
// 		while (comparator(((char*)array + i * size), middle) < 0)
// 			i++;
// 		// fprintf(stderr, "\nFor right elements\n");
// 		while (comparator(((char*)array + j * size), middle) > 0)
// 			j--;
// 		// fprintf(stderr, "\n");
//
// 		if (i <= j) {
// 			for (size_t k = 0; k < size; k++) {
// 				char tmp = *(((char*)array + i * size) + k);
// 				*(((char*)array + i * size) + k) = *(((char*)array + j * size) + k);
// 				*(((char*)array + j * size) + k) = tmp;
// 			}
//
// 			i++;
// 			j--;
//
// 			fprintf(stderr, "AFTER SWAP\n");
// 			fprintf(stderr, "cnt = %zu\n", cnt);
// 			fprintf(stderr, "array: ");
// 			for (size_t k = 0; k < cnt; k++) {
// 				fprintf(stderr, "%d ", *((char*)array + k * size));
// 			}
// 			fprintf(stderr, "\n");
// 			fprintf(stderr, "i = %zu, ", i);
// 			fprintf(stderr, "left = %d\n", *((char*)array + i * size));
// 			fprintf(stderr, "j = %zu, ", j);
// 			fprintf(stderr, "right = %d\n", *((char*)array + j * size));
// 			fprintf(stderr, "middle = %d\n", *middle);
// 			fprintf(stderr, "\n");
// 		}
//
// 	} while (i <= j);
//
// 	fprintf(stderr, "BEFORE RECURSION\n");
// 	fprintf(stderr, "cnt = %zu\n", cnt);
// 	fprintf(stderr, "array: ");
// 	for (size_t k = 0; k < cnt; k++) {
// 		fprintf(stderr, "%d ", *((char*)array + k * size));
// 	}
// 	fprintf(stderr, "\n");
// 	fprintf(stderr, "i = %zu, ", i);
// 	fprintf(stderr, "left = %d\n", *((char*)array + i * size));
// 	fprintf(stderr, "j = %zu, ", j);
// 	fprintf(stderr, "right = %d\n", *((char*)array + j * size));
// 	fprintf(stderr, "middle = %d\n", *middle);
// 	fprintf(stderr, "\n");
//
// 	if (j > 1)
// 		CustomQsort(array, j + 1, size, comparator);
// 	if (i < cnt) {
// 		fprintf(stderr, "BEFORE RIGHT SIDE SORT\n");
// 		fprintf(stderr, "cnt = %zu\n", cnt);
// 		fprintf(stderr, "i = %zu, ", i);
// 		fprintf(stderr, "left = %d\n", *((char*)array + i * size));
// 		fprintf(stderr, "j = %zu, ", j);
// 		fprintf(stderr, "right = %d\n", *((char*)array + j * size));
// 		fprintf(stderr, "middle = %d\n", *middle);
// 		fprintf(stderr, "array start element = %d\n", *(char*)array);
// 		fprintf(stderr, "\n");
// 		CustomQsort(((char*)array + (i - 1) * size), cnt - (j + 1), size, comparator);
// 	}
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

int CompareInt(const void* a, const void* b) {

	int _a = *(const int*)a;
	int _b = *(const int*)b;

	return _a - _b;

}

void SwapByByte(void* a, void* b, size_t size) {

	for (size_t i = 0; i < size; i++) {
		char tmp = *((char*)a + i);
		*((char*)a + i) = *((char*)b + i);
		*((char*)b + i) = tmp;
	}

}
