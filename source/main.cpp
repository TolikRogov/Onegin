#include "../include/StringFunctions.hpp"

int main() {

	errno = 0;

	Storage storage = {};

	StorageFiller(&storage);
	ONEGIN_ERROR_CHECK();

	SortingStrings(&storage);
	ONEGIN_ERROR_CHECK();

	StringPrinter(&storage);
	ONEGIN_ERROR_CHECK();

	StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK();

	return 0;
}
