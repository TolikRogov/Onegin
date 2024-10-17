#ifndef ONEGIN_INCLUDE
#define ONEGIN_INCLUDE

#include "utilities.hpp"

const size_t TRASH = 0xBEDA0DED0BEDA;

OneginStatusCode StringPrinter(String* text, size_t str_cnt, FILE* output);

OneginStatusCode StorageFiller(Storage* storage, const char* input_file_path);
OneginStatusCode StringsAddrFiller(Storage* storage);
OneginStatusCode StringFiller(Storage* storage);
OneginStatusCode StorageDestruct(Storage* storage);

OneginStatusCode FileSize(const char* file_path, size_t* size);
OneginStatusCode CharNewLineToZero(Storage* storage);

#endif //ONEGIN_INCLUDE
