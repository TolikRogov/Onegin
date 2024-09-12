#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>

enum OneginStatusCode {
	ONEGIN_NO_ERROR,
	ONEGIN_FILE_OPEN_ERROR,
	ONEGIN_FILE_READ_ERROR,
	ONEGIN_ALLOC_ERROR,
	ONEGIN_SORT_MODE_ERROR
};

struct FilePaths {
	const char* const onegin_ru = "data/onegin_ru.txt";
	const char* const onegin_en = "data/onegin_en.txt";
	const char* const output	= "data/output.txt";
};

struct String {
	char* cur_str;
	size_t cur_str_size;
};

struct Storage {
	char* buffer;
	size_t buffer_size;
	String** str_inf;
	size_t str_cnt;
	String** str_inf_original;
};

#define ONEGIN_ERROR_CHECK(status) {												 \
	if (status != ONEGIN_NO_ERROR) {												\
		fprintf(stderr, "Error code: %d, File: %20s, Function: %60s, Line: %3d \n", \
				status, __FILE__, __PRETTY_FUNCTION__, __LINE__);					\
		return status;																\
	}																				\
}

#endif //UTILITIES_INCLUDE
