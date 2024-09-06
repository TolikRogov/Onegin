#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintString(const char* string) {

	for (size_t i = 0; 1; i++) {
		printf("'%c'(%d)", *(string + i), *(string + i));

		if(*(string + i) == '\0')
			break;
	}

	printf("\n");
}

void Puts(const char* string) {
	printf("%s \n", string);
}

const char* Strchr(const char* string, char c) {

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

void Strcpy(char* string1, const char* string2) {

	for (size_t i = 0; ; i++) {
		*(string1 + i) = *(string2 + i);

		if(*(string2 + i) == '\0')
			break;
	}
}

char* Strncpy(char* string1, const char* string2, size_t count) {

	size_t i = 0;
	for (; (i < count) && (*(string2 + i) != '\0'); i++)
		*(string1 + i) = *(string2 + i);

	*(string1 + i) = '\0';

	return string1;
}

char* Strcat(char* string1, const char* string2) {

	size_t size_string1 = 0, size_string2 = 0;

	for (size_t i = 0; *(string1 + i) != '\0'; i++)
		size_string1++;

	printf("%zu \n", size_string1);

	for (size_t i = 0; *(string2 + i) != '\0'; i++) {
		//*(string1 + size_string1 + i) = *(string2 + i);
		size_string2++;
	}

	printf("%zu \n", size_string2);

// 	*(string1 + size_string1 + size_string2) = '\0';

	return string1;
}

int main() {

	const char* flag = "FLAG";
	const char* deadlock = "DEADLOCK";
	const char* eda = "EDA";
	char str3[] = {}, str4[] = {}, str5[100] = "DED ";

	Puts(flag);

	printf("addr of 'G' in str: %p \n", Strchr(flag, 'G'));
	printf("addr of str: %p \n", flag);
	printf("number of elements in str: %zu \n", Strlen(flag));

	Strcpy(str3, deadlock);
	PrintString(str3);

	Strncpy(str4, flag, 3);
 	PrintString(str4);

	Strcat(str5, eda);
	PrintString(str5);

	return 0;
}
