#include "../include/Onegin.hpp"
#include "../include/Sorting.hpp"

// TODO:
//	1) make custom qsort
//	2) color error check printf
//	Отличия bubble и lib-qsort

int main(int argc, char* argv[]) {

	clock_t start = clock();

	Storage storage = {};
	FilePaths file_paths = {};

	FILE* output = fopen(file_paths.output, "wb");
	if (!output)
		return ONEGIN_FILE_OPEN_ERROR;

	OneginStatusCode status = ONEGIN_NO_ERROR;

	status = StorageFiller(&storage, file_paths.onegin_en);
	ONEGIN_ERROR_CHECK(status);

	if (argc > 1) {

		OneginStatusCode (*Sort) (Storage*, SortingMode);

		if (!CustomStrcmpLeftRight(argv[1], "bubble-sort"))
			Sort = BubbleSort;
		else if (!CustomStrcmpLeftRight(argv[1], "lib-qsort"))
			Sort = LibraryQsort;
		else if (!CustomStrcmpLeftRight(argv[1], "custom-qsort"))
			Sort = CustomQsort;
		else
			goto error;

		for (size_t i = 0; i < 2; i++) {
			status = Sort(&storage, (SortingMode)i);
			ONEGIN_ERROR_CHECK(status);

			status = StringPrinter(storage.str_inf, storage.str_cnt, output);
			ONEGIN_ERROR_CHECK(status);
		}

	}
	else {
		error:
			status = ONEGIN_SORT_MODE_ERROR;
			ONEGIN_ERROR_CHECK(status);
	}

	status = StringPrinter(storage.str_inf_original, storage.str_cnt, output);
	ONEGIN_ERROR_CHECK(status);

	status = StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK(status);

	fclose(output);

	clock_t end = clock();
	WorkTime((double)(end - start), argv[1]);

	return 0;
}
