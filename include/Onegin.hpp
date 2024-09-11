#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ONEGIN_ERROR_CHECK(status) {												 \
	if (status != ONEGIN_NO_ERROR) {												\
		fprintf(stderr, "File: %s, Function: %s, Line: %d, Error code: %d \n",  	\
				__FILE__, __PRETTY_FUNCTION__, __LINE__, status);					\
		return status;																\
	}																				\
}

const size_t TRASH = 0xBEDA0DED0BEDA;

enum OneginStatusCode {
	ONEGIN_NO_ERROR,
	ONEGIN_FILE_OPEN_ERROR,
	ONEGIN_FILE_READ_ERROR,
	ONEGIN_ALLOC_ERROR
};

enum SortingMod {
	FROM_LEFT_TO_RIGHT,
	FROM_RIGHT_TO_LEFT
};

struct String {
	char* cur_str;
	size_t cur_str_size;
};

struct FilePaths {
	const char* const onegin_ru = "data/onegin_ru.txt";
	const char* const onegin_en = "data/onegin_en.txt";
	const char* const output_lr = "data/output_lr.txt";
	const char* const output_rl = "data/output_rl.txt";
};

struct Storage {
	char* buffer;
	size_t buffer_size;
	String** str_inf;
	size_t str_cnt;
};

OneginStatusCode StringPrinter(Storage* storage, const char* output_file_path);
OneginStatusCode LibraryQsort(Storage* storage, SortingMod mod);
OneginStatusCode StringsAddrFiller(Storage* storage);
OneginStatusCode StorageFiller(Storage* storage, const char* input_file_path);
OneginStatusCode FileSize(const char* file_path, size_t* size);
OneginStatusCode StorageDestruct(Storage* storage);
OneginStatusCode CharNewLineToZero(Storage* storage);
OneginStatusCode StringFiller(Storage* storage);
int CompareStringLeftRight(const void* str1, const void* str2);
int CustomStrcmpLeftRight(const char* string1, const char* string2);

#endif //UTILITIES_INCLUDE
