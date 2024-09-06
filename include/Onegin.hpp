#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include <errno.h>
#include <stdio.h>

#define ONEGIN_ERROR_CHECK() {													 	 \
	if (errno != ONEGIN_NO_ERROR)													\
		fprintf(stderr, "File: %s, Function: %s, Line: %d, Error code: %d \n",  	\
				__FILE__, __PRETTY_FUNCTION__, __LINE__, errno);					\
}

enum OneginStatusCode {
	ONEGIN_NO_ERROR,
	ONEGIN_FILE_ERROR,
	ONEGIN_ALLOC_ERROR
};

struct Storage {
	size_t buffer_size;
	char* buffer;
	size_t addr_size;
	char** addr;
};

OneginStatusCode StringPrinter(Storage* storage);
OneginStatusCode StringSort(Storage* storage);
OneginStatusCode AddrFiller(Storage* storage);
OneginStatusCode StorageFiller(Storage* storage);
OneginStatusCode FileSize(FILE* file, size_t* size);
OneginStatusCode StorageDestruct(Storage* storage);

#endif //UTILITIES_INCLUDE
