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

	storage->text = (String*)calloc(storage->str_cnt, sizeof(String));
	if (!storage->text)
		return ONEGIN_ALLOC_ERROR;

	storage->orig_text = (String*)calloc(storage->str_cnt, sizeof(String));
	if (!storage->text)
		return ONEGIN_ALLOC_ERROR;

	status = StringFiller(storage);
	ONEGIN_ERROR_CHECK(status);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringFiller(Storage* storage) {

	size_t cur_str_size = 0;
	size_t cur_str_num 	= 0;

	char* cur_str_pointer = storage->buffer;

	for (size_t i = 0; i < storage->buffer_size; i++) {

		cur_str_size++;

		if (*(storage->buffer + i) == '\0') {

			(*(storage->text + cur_str_num)).cur_str_size = cur_str_size;
			(*(storage->text + cur_str_num)).cur_str = cur_str_pointer;

			*(storage->orig_text + cur_str_num) = *(storage->text + cur_str_num);

			FillerDebugPrinter((storage->text + cur_str_num));

			cur_str_pointer = storage->buffer + i + 1;
			cur_str_num++;
			cur_str_size = 0;
		}
	}

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

	storage->str_cnt = TRASH;

	free(storage->text);
	storage->text = NULL;

	free(storage->orig_text);
	storage->orig_text = NULL;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringPrinter(String* text, size_t str_cnt, FILE* output) {

	for (size_t i = 0; i < str_cnt; i++) {
		*((*(text + i)).cur_str + (*(text + i)).cur_str_size - 1) = '\n';
		fwrite((*(text + i)).cur_str, sizeof(char), (*(text + i)).cur_str_size, output);
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

OneginStatusCode FillerDebugPrinter(const String* string) {

	static size_t str_num = 1;

	printf("String number: %zu \n", str_num);

	printf("Struct pointer: %p\n", string);

	printf("String pointer: %p\n", string->cur_str);

	printf("String: ('%d')", *(string->cur_str));
	printf("%s", string->cur_str);
	printf("('%d')\n", *(string->cur_str + string->cur_str_size - 2));

	printf("String size = %zu \n", string->cur_str_size);

	printf("\n");

	str_num++;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode WorkTime(double time, char* sort_type) {

	printf("Working Time with %s: %lf\n", sort_type, time / CLOCKS_PER_SEC);

	return ONEGIN_NO_ERROR;
}
