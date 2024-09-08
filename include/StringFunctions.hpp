#ifndef STRING_FUNCTIONS_INCLUDE
#define STRING_FUNCTIONS_INCLUDE

#include "../include/Onegin.hpp"

int CustomStrcmp(const char* string1, const char* string2);
OneginStatusCode PrintString(const char* string);
OneginStatusCode Puts(const char* string);
char* Strchr(char* string, int c);
size_t Strlen(const char* string);
char* Strcpy(char* string1, const char* string2);
char* Strncpy(char* string1, const char* string2, size_t count);

#endif //STRING_FUNCTIONS_INCLUDE
