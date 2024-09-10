#include "../include/StringFunctions.hpp"

struct stat FILE_STAT = {};

const char*  ONEGIN_FILE_PATH = "data/onegin.txt";

OneginStatusCode StorageFiller(Storage* storage) {

	FILE* input = fopen(ONEGIN_FILE_PATH, "r");
	if(!input)
		return ONEGIN_FILE_OPEN_ERROR;

	FileSize(ONEGIN_FILE_PATH, &storage->buf_inf.buffer_size);
	ONEGIN_ERROR_CHECK();

	storage->buf_inf.buffer = (char*)calloc(storage->buf_inf.buffer_size, sizeof(char));
	if (!storage->buf_inf.buffer)
		return ONEGIN_ALLOC_ERROR;

	size_t status = fread(storage->buf_inf.buffer, storage->buf_inf.buffer_size, sizeof(char), input);
	if (!status)
		return ONEGIN_FILE_READ_ERROR;

	StringsFiller(storage);
	ONEGIN_ERROR_CHECK();

	fclose(input);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringsFiller(Storage* storage) {

	CharNewLineToZero(storage);
	ONEGIN_ERROR_CHECK();

	storage->str_inf = (String**)calloc(storage->str_cnt, sizeof(String*));
	if (!storage->str_inf)
		return ONEGIN_ALLOC_ERROR;

	StringSizeCounter(storage);
	ONEGIN_ERROR_CHECK();

	FromBufferToString(storage);
	ONEGIN_ERROR_CHECK();

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FileSize(const char* file_path, size_t* size) {

	int stat = open(file_path, O_RDONLY);

	fstat(stat, &FILE_STAT);
	ONEGIN_ERROR_CHECK();

	*size = (size_t)FILE_STAT.st_size;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StorageDestruct(Storage* storage) {

	storage->buf_inf.buffer_size = TRASH;

	free(storage->buf_inf.buffer);
	storage->buf_inf.buffer = NULL;

	for (size_t i = 0; i < storage->str_cnt; i++) {
		free((*(storage->str_inf + i))->cur_str);
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

int CompareString(const void* str1, const void* str2) {

	const String* str1_inf = *((const String**)str1);
	const String* str2_inf = *((const String**)str2);

	return CustomStrcmp(str1_inf->cur_str, str2_inf->cur_str);

}

OneginStatusCode SortingStrings(Storage* storage) {

	qsort(storage->str_inf, storage->str_cnt, sizeof(String*), CompareString);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringPrinter(Storage* storage) {

	FILE* output = fopen("data/output.txt", "w");
	if (!output)
		return ONEGIN_FILE_OPEN_ERROR;

	for (size_t i = 0; i < storage->str_cnt; i++) {
		for (size_t j = 0; j < (*(storage->str_inf + i))->cur_str_size - 1; j++) {
			fprintf(output, "%c", *((*(storage->str_inf + i))->cur_str + j));
		}
		if (*((*(storage->str_inf + i))->cur_str) == '\0')
			continue;
		fprintf(output, "\n");
	}

	fclose(output);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode CharNewLineToZero(Storage* storage) {

	for (size_t i = 0; i < storage->buf_inf.buffer_size; i++) {
		if (*(storage->buf_inf.buffer + i) == '\n') {
			*(storage->buf_inf.buffer + i) = '\0';
			storage->str_cnt++;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringSizeCounter(Storage* storage) {

	size_t cur_str_size = 0, cur_str_num = 0;

	for (size_t i = 0; i < storage->buf_inf.buffer_size; i++) {

		cur_str_size++;

		if (*(storage->buf_inf.buffer + i) == '\0') {

			*(storage->str_inf + cur_str_num) = (String*)calloc(1, sizeof(String));
			if (!(*(storage->str_inf + cur_str_num)))
				return ONEGIN_ALLOC_ERROR;

			(*(storage->str_inf + cur_str_num))->cur_str_size = cur_str_size;

			cur_str_num++;
			cur_str_size = 0;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FromBufferToString(Storage* storage) {

	size_t* prev_sum_size = (size_t*)calloc(storage->str_cnt + 1, sizeof(size_t));
	if (!prev_sum_size)
		return ONEGIN_ALLOC_ERROR;

	for (size_t i = 0; i < storage->str_cnt; i++) {

		String* cur_str_inf = *(storage->str_inf + i);

		cur_str_inf->cur_str = (char*)calloc(cur_str_inf->cur_str_size, sizeof(char));
		if (!cur_str_inf->cur_str)
			return ONEGIN_ALLOC_ERROR;

		prev_sum_size[i + 1] = prev_sum_size[i] + cur_str_inf->cur_str_size;

		for (size_t j = 0; j < cur_str_inf->cur_str_size; j++)
			*(cur_str_inf->cur_str + j) = *(storage->buf_inf.buffer + prev_sum_size[i] + j);
	}

	free(prev_sum_size);
	prev_sum_size = NULL;

	return ONEGIN_NO_ERROR;
}
