#include "../include/StringFunctions.hpp"

// TODO:
//	1.5) sort with comparing only alpha
//	2) debug print in storage filler, FilterDebugPrint();
//	3) check error code from fstat
//	4) qsort comparator from right to left, with new comparator
//	5) print original text of the poem (new massive of pointers copied from storage before qsort) c помощью fwrite(buffer);

int main() {

	Storage storage = {};

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = StorageFiller(&storage);
	ONEGIN_ERROR_CHECK(status);

	status = SortingStrings(&storage);
	ONEGIN_ERROR_CHECK(status);

	status = StringPrinter(&storage);
	ONEGIN_ERROR_CHECK(status);

	status = StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK(status);

	return 0;
}
