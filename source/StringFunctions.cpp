#include <stdio.h>
#include <stdlib.h>

#include "../include/StringFunctions.hpp"

int CustomStrcmp(const char* string1, const char* string2) {

	for (size_t i = 0; ; i++) {
		if (*(string1 + i) != *(string2 + i))
			return *(string1 + i) - *(string2 + i);

		if ((*(string1 + i) == '\0') || (*(string2 + i) == '\0'))
			break;
	}

	return 0;
}

OneginStatusCode PrintString(const char* string) {

	for (size_t i = 0; 1; i++) {
		printf("'%c'(%d)", *(string + i), *(string + i));

		if(*(string + i) == '\0')
			break;
	}

	printf("\n");

	return ONEGIN_NO_ERROR;
}

OneginStatusCode Puts(const char* string) {

	printf("%s \n", string);

	return ONEGIN_NO_ERROR;
}

char* Strchr(char* string, int c) {

	for (size_t i = 0; *(string + i) != '\0'; i++) {
		if (*(string + i) == c)
			return (string + i);
	}

	return NULL;
}

size_t Strlen(const char* string) {

	size_t len = 0;

	for (size_t i = 0; *(string + i) != '\0'; i++) {
		len++;
	}

	return len;
}

char* Strcpy(char* string1, const char* string2) {

	for (size_t i = 0; ; i++) {
		*(string1 + i) = *(string2 + i);

		if(*(string2 + i) == '\0')
			break;
	}

	return string1;
}

char* Strncpy(char* string1, const char* string2, size_t count) {

	size_t i = 0;
	for (; (i < count) && (*(string2 + i) != '\0'); i++)
		*(string1 + i) = *(string2 + i);

	*(string1 + i) = '\0';

	return string1;
}
