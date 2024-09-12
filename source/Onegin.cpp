#include "../include/Onegin.hpp"

struct stat FILE_STAT = {};

OneginStatusCode StorageFiller(Storage* storage, const char* input_file_path) {

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = FileSize(input_file_path, &storage->buffer_size);
	ONEGIN_ERROR_CHECK(status);

	FILE* input = fopen(input_file_path, "rb");
	if(!input)
		return ONEGIN_FILE_OPEN_ERROR;

	storage->buffer = (char*)calloc(storage->buffer_size, sizeof(char));
	if (!storage->buffer)
		return ONEGIN_ALLOC_ERROR;

	size_t read_inf_cnt = fread(storage->buffer, storage->buffer_size, sizeof(char), input);
	if (!read_inf_cnt)
		return ONEGIN_FILE_READ_ERROR;

	status = StringsAddrFiller(storage);
	ONEGIN_ERROR_CHECK(status);

	fclose(input);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringsAddrFiller(Storage* storage) {

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = CharNewLineToZero(storage);
	ONEGIN_ERROR_CHECK(status);

	storage->str_inf = (String**)calloc(storage->str_cnt, sizeof(String*));
	if (!storage->str_inf)
		return ONEGIN_ALLOC_ERROR;

	status = StringFiller(storage);
	ONEGIN_ERROR_CHECK(status);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FileSize(const char* file_path, size_t* size) {

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = (OneginStatusCode)stat(file_path, &FILE_STAT);
	ONEGIN_ERROR_CHECK(status);

	*size = (size_t)FILE_STAT.st_size;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StorageDestruct(Storage* storage) {

	storage->buffer_size = TRASH;

	free(storage->buffer);
	storage->buffer = NULL;

	for (size_t i = 0; i < storage->str_cnt; i++) {
		(*(storage->str_inf + i))->cur_str = NULL;

		(*(storage->str_inf + i))->cur_str_size = TRASH;

		free(*(storage->str_inf));
		(*(storage->str_inf)) = NULL;
	}

	free(storage->str_inf);
	storage->str_inf = NULL;

	storage->str_cnt = TRASH;

	return ONEGIN_NO_ERROR;
}

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

OneginStatusCode StringPrinter(Storage* storage, FILE* output) {

	for (size_t i = 0; i < storage->str_cnt; i++) {
		*((*(storage->str_inf + i))->cur_str + (*(storage->str_inf + i))->cur_str_size - 1) = '\n';
		fwrite((*(storage->str_inf + i))->cur_str, sizeof(char), (*(storage->str_inf + i))->cur_str_size, output);
	}

	fprintf(output, "\n");

	return ONEGIN_NO_ERROR;
}

OneginStatusCode CharNewLineToZero(Storage* storage) {

	for (size_t i = 0; i < storage->buffer_size; i++) {
		if (*(storage->buffer + i) == '\n') {
			*(storage->buffer + i) = '\0';
			storage->str_cnt++;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringFiller(Storage* storage) {

	size_t cur_str_size = 0;
	size_t cur_str_num 	= 0;

	char* cur_str_pointer = storage->buffer;

	for (size_t i = 0; i < storage->buffer_size; i++) {

		cur_str_size++;

		if (*(storage->buffer + i) == '\0') {

			*(storage->str_inf + cur_str_num) = (String*)calloc(1, sizeof(String));
			if (!(*(storage->str_inf + cur_str_num)))
				return ONEGIN_ALLOC_ERROR;

			(*(storage->str_inf + cur_str_num))->cur_str_size = cur_str_size;
			(*(storage->str_inf + cur_str_num))->cur_str = cur_str_pointer;

			cur_str_pointer = storage->buffer + i + 1;
			cur_str_num++;
			cur_str_size = 0;
		}
	}

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
