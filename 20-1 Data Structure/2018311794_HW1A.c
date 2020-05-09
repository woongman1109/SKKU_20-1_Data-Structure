#include <stdio.h>
#include <string.h>
#define MAX_STACK 100

typedef enum {
	false,
	true
} bool;

typedef struct {
	char palin[MAX_STACK];
	int top;
} Stack;

void initStack(Stack* pstack);
bool isFull(Stack* pstack);
bool isEmpty(Stack* pstack);

char Peek(Stack* pstack);
void Push(Stack* pstack, char c);
void Pop(Stack* pstack);

int main() {

	Stack seq, comp;
	char pl[MAX_STACK];
	int pl_len, diff = 0;

	// printf("Characters: ");
	scanf("%s", pl);
	pl_len = strlen(pl);
	initStack(&seq);
	initStack(&comp);

	// printf("\nYour word: %s", pl);

	for (int i = 0; i < pl_len; i++) {
		Push(&seq, pl[i]);
		Push(&comp, pl[pl_len - i -1]);
	}

	for (int i = 0; i < pl_len; i++) {
		if (Peek(&seq) != Peek(&comp)) {
			diff++;
			// printf("%c | %c\n", Peek(&seq), Peek(&comp));
		}
		Pop(&seq); Pop(&comp);
	}

	printf("%d", diff);

	return 0;
}

void initStack(Stack* pstack) {
	pstack->top = -1;
}
bool isFull(Stack* pstack) {
	return pstack->top == MAX_STACK - 1;
}
bool isEmpty(Stack* pstack) {
	return pstack->top == -1;
}

char Peek(Stack* pstack) {
	if (isEmpty(pstack)) {
		printf("\n[ERROR]: Your stack did not have an element...\n");
		exit(1);
	}
	return pstack->palin[pstack->top];
}

void Push(Stack* pstack, char c) {
	pstack->top++;
	pstack->palin[pstack->top] = c;
}

void Pop(Stack* pstack) {
	if (isEmpty(pstack)) {
		printf("\n[ERROR]: Your stack did not have an element...\n");
		exit(1);
	}
	--(pstack->top);
}