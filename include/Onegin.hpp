#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ONEGIN_ERROR_CHECK() {													 	 \
	if (errno != ONEGIN_NO_ERROR)													\
		fprintf(stderr, "File: %s, Function: %s, Line: %d, Error code: %d \n",  	\
				__FILE__, __PRETTY_FUNCTION__, __LINE__, errno);					\
}

const size_t TRASH = 0xBEDA0DED0BEDA;

enum OneginStatusCode {
	ONEGIN_NO_ERROR,
	ONEGIN_FILE_OPEN_ERROR,
	ONEGIN_FILE_READ_ERROR,
	ONEGIN_ALLOC_ERROR
};

struct Buffer {
	char* buffer;
	size_t buffer_size;
};

struct String {
	char* cur_str;
	size_t cur_str_size;
};

struct Storage {
	Buffer buf_inf;
	String** str_inf;
	size_t str_cnt;
};

OneginStatusCode StringPrinter(Storage* storage);
OneginStatusCode SortingStrings(Storage* storage);
OneginStatusCode StringsFiller(Storage* storage);
OneginStatusCode StorageFiller(Storage* storage);
OneginStatusCode FileSize(const char* file_path, size_t* size);
OneginStatusCode StorageDestruct(Storage* storage);
OneginStatusCode CharNewLineToZero(Storage* storage);
OneginStatusCode StringSizeCounter(Storage* storage);
OneginStatusCode FromBufferToString(Storage* storage);
int CompareString(const void* str1, const void* str2);

#endif //UTILITIES_INCLUDE
