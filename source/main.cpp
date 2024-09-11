#include "../include/Onegin.hpp"

// TODO:
//	2) debug print in storage filler, FilterDebugPrint();
//	3) check error code from fstat
//	4) qsort comparator from right to left, with new comparator
//	5) print original text of the poem (new massive of pointers copied from storage before qsort) c помощью fwrite(buffer);

int main() {

	Storage storage = {};
	FilePaths file_paths = {};

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = StorageFiller(&storage, file_paths.onegin_en);
	ONEGIN_ERROR_CHECK(status);

	status = LibraryQsort(&storage, FROM_LEFT_TO_RIGHT);
	ONEGIN_ERROR_CHECK(status);

	status = StringPrinter(&storage, file_paths.output_lr);
	ONEGIN_ERROR_CHECK(status);

	status = StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK(status);

	return 0;
}
