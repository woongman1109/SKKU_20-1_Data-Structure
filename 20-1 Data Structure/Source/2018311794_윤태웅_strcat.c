#include <stdio.h>
#include <string.h>
#define FREE(pointer) (free(pointer), (pointer) = NULL)

char* mygets(char* s) {
	int size = 50;
	char* tmp = (char*)malloc(sizeof(char) * size);
	char buffer = '0';
	int l = 0;

	do {
		if (l >= size * 0.8) {
			realloc(tmp, size * 2);
			size *= 2;
		}

		buffer = (char)getchar();
		if (buffer != '\n') {
			tmp[l] = buffer;
			l++;
		}
		else {
			tmp[l] = '\0';
			break;
		}

	} while (1);
	rewind(stdin);

	s = realloc(tmp, size);
	return s;
}

char* catmeow(char* s1, char* s2) {
	int s1_len = strlen(s1);
	realloc(s1, s1_len + strlen(s2) + 1);
	// For general purpose(without mygets()): Compare with the size of the array, not the length of string

	int i = 0;
	for (i; i < strlen(s2); i++) {
		s1[s1_len + i] = s2[i];
	}
	s1[s1_len+i] = '\0';

	printf("str1: %s\n", s1);
	return s1;
}

int main() {
	char* str1 = (char*)malloc(sizeof(char) * 10);
	char* str2 = (char*)malloc(sizeof(char) * 10);

	printf("Input string1: ");
	str1 = mygets(str1);
	printf("Input string2: ");
	str2 = mygets(str2);
	// printf("str1: %s\nstr2: %s\n", str1, str2);
	// printf("\n=== str1_len: %d || str2_len: %d ===\n", strlen(str1), strlen(str2));

	str1 = catmeow(str1, str2);
	printf("\nConcatenated string: %s\n\n", str1);

	FREE(str2);
	FREE(str1);
	return 0;
}