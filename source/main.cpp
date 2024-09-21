#include "../include/Onegin.hpp"
#include "../include/Sorting.hpp"

int main(int argc, const char* argv[]) {

#ifdef LOG_FILE_SORT
	clock_t start = clock();
#endif

	OneginStatusCode status = ONEGIN_NO_ERROR;

	if (argc < 3)
		ONEGIN_ERROR_CHECK(ONEGIN_FEW_ARG_ERROR);

	Storage   storage 	= {};
	FilePaths file_paths = {};

	compare_func_t comparators[] = { CompareStringLeftRight, CompareStringRightLeft };

#ifdef LOG_FILE_SORT
	HtmlLogStarter();
#endif

	void (*Sort) (void*, size_t, size_t, compare_func_t) = NULL;

	if (!StrCmp(argv[2], "bubble-sort"))
		Sort = BubbleSort;
	else if (!StrCmp(argv[2], "lib-qsort"))
		Sort = qsort;
	else if (!StrCmp(argv[2], "custom-qsort"))
		Sort = CustomQsort;
	else
		ONEGIN_ERROR_CHECK(ONEGIN_SORT_MODE_ERROR);

	FILE* output = fopen(file_paths.output, "wb");
	if (!output)
		ONEGIN_ERROR_CHECK(ONEGIN_FILE_OPEN_ERROR);

	status = StorageFiller(&storage, argv[1]);
	ONEGIN_ERROR_CHECK(status);

	for (size_t i = 0; i < 2; i++) {

		Sort(storage.text, storage.str_cnt, sizeof(String), comparators[i]);

		status = StringPrinter(storage.text, storage.str_cnt, output);
		ONEGIN_ERROR_CHECK(status);

	}

	status = StringPrinter(storage.orig_text, storage.str_cnt, output);
	ONEGIN_ERROR_CHECK(status);

	status = StorageDestruct(&storage);
	ONEGIN_ERROR_CHECK(status);

	fclose(output);

#ifdef LOG_FILE_SORT
	clock_t end = clock();
	WorkTime((double)(end - start), argv[2]);

	HtmlLogFinisher();
#endif

	return 0;
}
