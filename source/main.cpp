#include <stdio.h>
#include <stdlib.h>

void Puts(char* string) {
	printf("%s \n", string);
}

char* Strchr(char* string, char c) {
	for (size_t i = 0; *(string + i) != '\0'; i++) {
		if (*(string + i) == c)
			return (string + i);
	}

	return NULL;
}

size_t Strlen(char* string) {

	size_t len = 0;

	for (size_t i = 0; *(string + i) != '\0'; i++) {
		len++;
	}

	return len;
}

// void Strcpy(char* string1, char* string2) {
//
// 	size_t size = Strlen(string2);
//
// 	string1 = (char*)realloc(string1, size * sizeof(char));
//
// 	for (size_t i = 0; *(string2 + i) != '\0'; i++) {
// 		*(string1 + i) = *(string2 + i);
// 	}
// }

int main() {

	char str[] = "FLAG";
	char str2[] = "DEADLOCK";
	Puts(str);
	printf("\n %p \n", Strchr(str, 'G'));
	printf(" %p \n", &str);
	printf(" %zu \n", Strlen(str));
	Strcpy(str, str2);
	Puts(str);

	return 0;
}
