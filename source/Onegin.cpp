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

	storage->str_inf_original = (String**)calloc(storage->str_cnt, sizeof(String*));
	if (!storage->str_inf_original)
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

	free(storage->str_inf_original);
	storage->str_inf_original = NULL;

	storage->str_cnt = TRASH;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringPrinter(String** str_inf, size_t str_cnt, FILE* output) {

	for (size_t i = 0; i < str_cnt; i++) {
		*((*(str_inf + i))->cur_str + (*(str_inf + i))->cur_str_size - 1) = '\n';
		fwrite((*(str_inf + i))->cur_str, sizeof(char), (*(str_inf + i))->cur_str_size, output);
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

			*(storage->str_inf_original + cur_str_num) = *(storage->str_inf + cur_str_num);

			(*(storage->str_inf + cur_str_num))->cur_str_size = cur_str_size;
			(*(storage->str_inf + cur_str_num))->cur_str = cur_str_pointer;

			FillerDebugPrinter((*(storage->str_inf + cur_str_num)));

			cur_str_pointer = storage->buffer + i + 1;
			cur_str_num++;
			cur_str_size = 0;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FillerDebugPrinter(String* string) {

	static size_t str_num = 1;

	printf("String number: %zu \n", str_num);

	printf("('%d')", *string->cur_str);
	printf("%s \n", string->cur_str);

	printf("String size = %zu \n", string->cur_str_size);

	printf("\n");

	str_num++;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode WorkTime(double time, char* sort_type) {

	printf("Working Time with %s: %lf\n", sort_type, time / CLOCKS_PER_SEC);

	return ONEGIN_NO_ERROR;
}
