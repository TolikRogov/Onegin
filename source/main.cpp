#include "../include/Onegin.hpp"

int main() {

	Storage storage = {};
	FilePaths file_paths = {};

	FILE* output = fopen(file_paths.output, "wb");
	if (!output)
		return ONEGIN_FILE_OPEN_ERROR;

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = StorageFiller(&storage, file_paths.onegin_en);
	ONEGIN_ERROR_CHECK(status);


	status = LibraryQsort(&storage, FROM_LEFT_TO_RIGHT);
	ONEGIN_ERROR_CHECK(status);

	status = StringPrinter(storage.str_inf, storage.str_cnt, output);
	ONEGIN_ERROR_CHECK(status);


	status = LibraryQsort(&storage, FROM_RIGHT_TO_LEFT);
	ONEGIN_ERROR_CHECK(status);

	status = StringPrinter(storage.str_inf, storage.str_cnt, output);
	ONEGIN_ERROR_CHECK(status);


	status = StringPrinter(storage.str_inf_original, storage.str_cnt, output);
	ONEGIN_ERROR_CHECK(status);


	status = StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK(status);

	fclose(output);

	return 0;
}
