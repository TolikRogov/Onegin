#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define ONEGIN_ERROR_CHECK(status) {																	 		 \
	if (status != ONEGIN_NO_ERROR) {																			\
		fprintf(stderr, "\033[31;1mError code: %d,\033[0m \033[33;4mFile: %s, Function: %s, Line: %d \n\033[0m",\
				status, __FILE__, __PRETTY_FUNCTION__, __LINE__);												\
		return status;																							\
	}																											\
}

typedef int  (*compare_func_t) (const void*, const void*);
typedef void (*sort_func_t)	   (void*, size_t, size_t, compare_func_t);

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

	String* text;
	String* orig_text;
	size_t str_cnt;
};

#endif //UTILITIES_INCLUDE
