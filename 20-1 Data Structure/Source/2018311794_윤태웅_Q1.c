//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int getArrayElements(int* arr) {
//	char* str[50] = {0};
//	char* el;
//	int i = 0;
//	printf("Input array elements: ");
//	scanf("%[^\n]s", str);
//
//	el = strtok(str, " ,");
//	while (el != NULL) {
//		arr[i++] = atoi(el);
//		el = strtok(NULL, " ,");
//	}
//	return i;
//}
//
//void insertElement(int e, int p, int* arr, int len, int* newArr) {
//	int j = 0;
//	for (int i = 0; i < len; i++) {
//		if (j != p - 1) 
//			newArr[j] = arr[i];
//		else {
//			newArr[j] = e;
//			i--;
//		}
//		j++;
//	}
//}
//
//int main() {
//	int* array[50] = {0};
//	int len, add, pos;
//	len = getArrayElements(array);
//	int* newArr = (int*)calloc(len + 1, sizeof(int));
//
//	printf("Input element to insert: ");
//	scanf("%d", &add);
//	printf("\n");
//
//	do {
//		printf("Input position where to insert: ");
//		scanf("%d", &pos);
//
//		if (pos<0 || pos>len + 1) {
//			printf("[ERROR] Position is invalid. Check the length of array.\n\n");
//		}
//		else {
//			insertElement(add, pos, array, len, newArr);
//			break;
//		}
//	} while (1);
//	
//	printf("\nElements of array are: ");
//	for (int i = 0; i < len + 1; i++) {
//		printf("%d", newArr[i]);
//		if (i != len)
//			printf(", ");
//	} printf("\n");
//
//	free(newArr);
//
//	return 0;
//}