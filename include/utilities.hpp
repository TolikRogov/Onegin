#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define ONEGIN_ERROR_CHECK(status) {																	 		 		\
	if (status != ONEGIN_NO_ERROR) {																					\
		fprintf(stderr, "\033[31;1mError (code %d): %s,\033[0m \033[33;4mFile: %s, Function: %s, Line: %d \n\033[0m",   \
				status, ErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);								\
		fclose(stderr);																									\
		return status;																									\
	}																													\
}

typedef int  (*compare_func_t) (const void*, const void*);
typedef void (*sort_func_t)	   (void*, size_t, size_t, compare_func_t);

enum OneginStatusCode {
	ONEGIN_NO_ERROR,
	ONEGIN_FILE_OPEN_ERROR,
	ONEGIN_FILE_READ_ERROR,
	ONEGIN_ALLOC_ERROR,
	ONEGIN_FEW_ARG_ERROR,
	ONEGIN_SORT_MODE_ERROR,
	ONEGIN_INPUT_FILE_ERROR
};

struct FilePaths {
	const char* const output	= "data/output.txt";
	const char* const log_html  = "log_eblan.html";
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

OneginStatusCode FillerDebugPrinter(const String* string);
OneginStatusCode WorkTime(double time, const char* sort_type);
OneginStatusCode HtmlLogStarter();
OneginStatusCode HtmlLogFinisher();
const char* ErrorsMessenger(OneginStatusCode status);

#endif //UTILITIES_INCLUDE
