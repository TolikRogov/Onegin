#include "../include/Onegin.hpp"

OneginStatusCode StorageFiller(Storage* storage, const char* input_file_path) {

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = FileSize(input_file_path, &storage->buffer_size);
	ONEGIN_ERROR_CHECK(status);

	FILE* input = fopen(input_file_path, "rb");
	if(!input)
		return ONEGIN_FILE_OPEN_ERROR;

	storage->buffer = (char*)calloc(storage->buffer_size, sizeof(char));
	if (!storage->buffer) {
		StorageDestruct(storage);
		return ONEGIN_ALLOC_ERROR;
	}

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
	if (!storage->text) {
		StorageDestruct(storage);
		return ONEGIN_ALLOC_ERROR;
	}

	storage->orig_text = (String*)calloc(storage->str_cnt, sizeof(String));
	if (!storage->text) {
		StorageDestruct(storage);
		return ONEGIN_ALLOC_ERROR;
	}

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

#ifdef LOG_FILE_SORT
			FillerDebugPrinter((storage->text + cur_str_num));
#endif

			cur_str_pointer = storage->buffer + i + 1;
			cur_str_num++;
			cur_str_size = 0;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FileSize(const char* file_path, size_t* size) {

	struct stat file_stat = {};

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = (OneginStatusCode)stat(file_path, &file_stat);
	ONEGIN_ERROR_CHECK(status);

	*size = (size_t)file_stat.st_size;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StorageDestruct(Storage* storage) {

	storage->buffer_size = TRASH;

	if (storage->buffer) {
		free(storage->buffer);
		storage->buffer = NULL;
	}

	storage->str_cnt = TRASH;

	if (storage->text) {
		free(storage->text);
		storage->text = NULL;
	}

	if (storage->orig_text) {
		free(storage->orig_text);
		storage->orig_text = NULL;
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringPrinter(String* text, size_t str_cnt, FILE* output) {

	for (size_t i = 0; i < str_cnt; i++)
		fprintf(output, "%s\n", (*(text + i)).cur_str);

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
