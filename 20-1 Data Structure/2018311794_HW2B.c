#include <stdio.h>
#include <stdlib.h>
typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

void printList(Node* head) {
	Node* ptr = head;
	while (ptr) {
		printf("%d ", ptr->data);
		printf("-> ");
		ptr = ptr->next;
	}
	printf("NULL");
	printf("\n");
}

void push(Node** head, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

Node* Reserve(Node* head, int g) {
	if (g == 1)
		return head;
	Node* prev = NULL, * gprev = head, * tprev = NULL, *cur = head;
	Node* nxt = cur->next;
	int i = 0, h = 0;
	while (nxt) {
		while (i < g && nxt != NULL) {
			if (!i)
				tprev = cur;
			prev = cur;
			cur = nxt;
			nxt = nxt->next;
			if ( i++ != g )
				cur->next = prev;
		}
		
		if (!h++) {
			if (nxt) {
				head = prev;
				gprev = tprev;
			}
			else {
				head = cur;
			}
		}
		else if (nxt) {
			gprev->next = prev;
			gprev = tprev;
			i = 0;
		}
		if(h && !nxt)
			gprev->next = cur;
	}
	tprev->next = NULL;
	return head;
}

int main() {
	int N, list[100], g;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
	Node* head = NULL;
	scanf("%d", &g);
	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	printList(head);
	head = Reserve(head, g);
	printList(head);
	return 0;
}