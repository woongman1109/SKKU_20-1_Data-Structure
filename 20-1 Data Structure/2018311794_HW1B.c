#include <stdio.h>
#include <string.h>

#define MAX 100

typedef enum {
	false,
	true
} bool;

typedef struct {
	int front, rear;
	char palin[MAX];
} Queue;

void initQueue(Queue* pqueue);
bool isQueueFull(Queue* pqueue);
bool isQueueFull(Queue* pqueue);

char PeekQueue(Queue* pqueue);
void EnQueue(Queue* pqueue, char c);
void DeQueue(Queue* pqueue);


int main() {

	Queue seq1, seq2, comp;
	char str[MAX], e, myPalin[MAX];
	int pl_len, j = 0;
	bool isDecal = 1;
	char forDecal = '\0';

	printf("Your string: ");
	scanf("%s", str);
	pl_len = strlen(str);
	
	initQueue(&seq1);
	initQueue(&seq2);
	initQueue(&comp);
	for (int i = 0; i < pl_len; i++) {
		EnQueue(&seq1, str[i]);
		EnQueue(&comp, str[i]);
	}

	// int h = 0;
	while (!isQueueEmpty(&comp)) {
		// printf("============%d===========\n", h++);
		int k = 0, f;
		e = PeekQueue(&comp);
		DeQueue(&comp);
		DeQueue(&seq1);
		f = seq1.front;
		while (1) {
			if (isQueueEmpty(&seq1)) {
				str[k] = '\0';
				// printf("str체크 = %d: %s\n", h, str);

				for (int n = 0; n < k; n++) {
					// printf("중복없음 - seq1 채우기\n");
					isDecal = 0;
					forDecal = e;
					EnQueue(&seq1, str[n]);
				}
				break;
			}
			if (e == PeekQueue(&seq1)) {
				myPalin[j++] = e;
				// printf("중복: %c\n", e);

				for (int i = f; i < seq1.front; i++) {
					// printf("%d seq1 앞부분 채우기 시작\n",i);
					EnQueue(&seq2, PeekQueue(&comp));
					DeQueue(&comp);
				}
				DeQueue(&seq1);
				initQueue(&comp);

				while (!isQueueEmpty(&seq1)) {
					// printf("seq1 뒷부분 채우기 시작\n");
					str[k++] = PeekQueue(&seq1);
					EnQueue(&seq2, PeekQueue(&seq1));
					DeQueue(&seq1);
				}
				while (!isQueueEmpty(&seq2)) {
					// printf("comp 다시 채우기\n");
					EnQueue(&comp, PeekQueue(&seq2));
					DeQueue(&seq2);
				}
				for (int n = 0; n < k; n++) {
					// printf("seq1 다시 채우기\n");
					EnQueue(&seq1, str[n]);
				}
				break;
			}
			str[k++] = PeekQueue(&seq1);
			DeQueue(&seq1);
		}
	}
	if (isDecal == false)
		myPalin[j] = forDecal;
	int h = 0;
	while (j >= h) {
		myPalin[j + (h++)] = myPalin[j - h];
	}
	myPalin[j + h] = '\0';

	printf("%s", myPalin);


	return 0;
}


void initQueue(Queue* pqueue) {
	pqueue->front = pqueue->rear = 0;
}
bool isQueueFull(Queue* pqueue) {
	return pqueue->front == (pqueue->rear +1) % MAX;
}
bool isQueueEmpty(Queue* pqueue) {
	return pqueue->front == pqueue->rear;
}


char PeekQueue(Queue* pqueue) {
	if(isQueueEmpty(pqueue)) {
		printf("\n[ERROR - Peek]: Your stack did not have an element...\n");
		exit(1);
	}
	return pqueue->palin[pqueue->front];
}
void EnQueue(Queue* pqueue, char c) {
	if(isQueueFull(pqueue)) {
		printf("\n[ERROR - EnQueue]: Your stack was full...\n");
		exit(1);
	}
	pqueue->palin[pqueue->rear] = c;
	pqueue->rear = (pqueue->rear + 1) % MAX;
}
void DeQueue(Queue* pqueue) {
	if (isQueueEmpty(pqueue)) {
		printf("\n[ERROR - DeQueue]: Your stack did not have an element...\n");
		exit(1);
	}

	pqueue->front = (pqueue->front + 1) % MAX;
}