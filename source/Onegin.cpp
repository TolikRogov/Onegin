#include <stdio.h>
#include <stdlib.h>

#include "../include/Onegin.hpp"
#include "../include/StringFunctions.hpp"

OneginStatusCode StorageFiller(Storage* storage) {

	FILE* input = fopen("data/onegin.txt", "r");
	if(!input)
		return ONEGIN_FILE_ERROR;

	FileSize(input, &storage->buffer_size);
	ONEGIN_ERROR_CHECK();

	storage->buffer = (char*)calloc(storage->buffer_size, sizeof(char));
	if (!storage->buffer)
		return ONEGIN_ALLOC_ERROR;

	fread(storage->buffer, storage->buffer_size, sizeof(char), input);

	AddrFiller(storage);
	ONEGIN_ERROR_CHECK();

	fclose(input);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode AddrFiller(Storage* storage) {

	for (size_t i = 0; i < storage->buffer_size; i++) {
		if (*(storage->buffer + i) == '\n') {
			*(storage->buffer + i) = '\0';
			storage->addr_size++;
		}
	}

	storage->addr = (char**)calloc(storage->addr_size, sizeof(char*));
	if (!storage->addr)
		return ONEGIN_ALLOC_ERROR;

	*storage->addr = storage->buffer;
	size_t cur_line_cnt = 1;
	for (size_t i = 1; i < storage->buffer_size; i++) {
		if (*(storage->buffer + i - 1) == '\0') {
			*(storage->addr + cur_line_cnt) = (storage->buffer + i);
			cur_line_cnt++;
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode FileSize(FILE* file, size_t* size) {

	int cur_plc = (int)ftell(file);
	fseek(file, 0, SEEK_END);
	*size = (size_t)ftell(file);
	fseek(file, 0, cur_plc);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StorageDestruct(Storage* storage) {

	storage->addr_size = 0;
	storage->buffer_size = 0;

	free(storage->addr);
	storage->addr = NULL;

	free(storage->buffer);
	storage->buffer = NULL;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringSort(Storage* storage) {

	for (size_t i = 0; i < storage->addr_size - 1; i++) {
		for (size_t j = i + 1; j < storage->addr_size; j++) {
			if (Strcmp(*(storage->addr + i), *(storage->addr + j)) > 0) {
				char* tmp = (*(storage->addr + i));
				*(storage->addr + i) = *(storage->addr + j);
				*(storage->addr + j) = tmp;
			}
		}
	}

	return ONEGIN_NO_ERROR;
}

OneginStatusCode StringPrinter(Storage* storage) {

	for (size_t i = 0; i < storage->addr_size; i++) {
		for (size_t j = 0; *(*(storage->addr + i) + j) != '\0'; j++) {
			printf("%c", *(*(storage->addr + i) + j));
		}
		printf("\n");
	}

	return ONEGIN_NO_ERROR;
}
