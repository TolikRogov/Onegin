#include <stdio.h>
#include <stdlib.h>

#include "../include/Onegin.hpp"
#include "../include/StringFunctions.hpp"

// TODO:
//	1) git ignore на build
//	2) const variables for destruct function

int main() {

	errno = 0;

	Storage storage = {};

	StorageFiller(&storage);
	ONEGIN_ERROR_CHECK();

	Bubble(&storage);
	ONEGIN_ERROR_CHECK();

	StringPrinter(&storage);
	ONEGIN_ERROR_CHECK();

	StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK();

	return 0;
}
