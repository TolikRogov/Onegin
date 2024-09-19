#include "../include/Onegin.hpp"
#include "../include/Sorting.hpp"

int main(int argc, char* argv[]) {

#ifdef LOG_FILE_SORT
	clock_t start = clock();
#endif

	OneginStatusCode status = ONEGIN_NO_ERROR;

	if (argc > 1) {

		Storage   storage 	= {};
		FilePaths file_paths = {};

		compare_func_t comparators[] = { CompareStringLeftRight, CompareStringRightLeft };

		FILE* output = fopen(file_paths.output, "wb");
		if (!output)
			return ONEGIN_FILE_OPEN_ERROR;

#ifdef LOG_FILE_SORT
		HtmlLogStarter();
#endif

		status = StorageFiller(&storage, file_paths.onegin_en);
		ONEGIN_ERROR_CHECK(status);

		void (*Sort) (void*, size_t, size_t, compare_func_t) = nullptr;

		if (!CustomStrcmpLeftRight(argv[1], "bubble-sort"))
			Sort = BubbleSort;
		else if (!CustomStrcmpLeftRight(argv[1], "lib-qsort"))
			Sort = qsort;
		else if (!CustomStrcmpLeftRight(argv[1], "custom-qsort"))
			Sort = CustomQsort;
		else
			goto error;

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
		WorkTime((double)(end - start), argv[1]);

		HtmlLogFinisher();
#endif

	}
	else {
		error:
			status = ONEGIN_SORT_MODE_ERROR;
			ONEGIN_ERROR_CHECK(status);
	}

	return 0;
}
