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

struct String {
	char* cur_str;
	size_t cur_str_size;
};

struct FilePaths {
	const char* const ru_onegin_file_path = "data/onegin_ru.txt";
	const char* const en_onegin_file_path = "data/onegin_en.txt";
	const char* const output_file_path 	  = "data/output.txt";
};

struct Storage {
	char* buffer;
	size_t buffer_size;
	String** str_inf;
	size_t str_cnt;
};

OneginStatusCode StringPrinter(Storage* storage);
OneginStatusCode SortingStrings(Storage* storage);
OneginStatusCode StringsAddrFiller(Storage* storage);
OneginStatusCode StorageFiller(Storage* storage);
OneginStatusCode FileSize(const char* file_path, size_t* size);
OneginStatusCode StorageDestruct(Storage* storage);
OneginStatusCode CharNewLineToZero(Storage* storage);
OneginStatusCode StringFiller(Storage* storage);
int CompareString(const void* str1, const void* str2);

#endif //UTILITIES_INCLUDE
