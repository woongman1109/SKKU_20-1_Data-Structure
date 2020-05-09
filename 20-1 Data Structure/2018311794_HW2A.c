#include <stdio.h>
#include <stdlib.h>
typedef struct _Node
{
	int data;
	struct _Node* next;
}Node;

void printList(Node* head)
{
	Node* ptr = head;
	while (ptr)
	{
		printf("%d ", ptr->data);
		printf("-> ");
		ptr = ptr->next;
	}
	printf("NULL");
	printf("\n");
}

void push(Node** head, int data)
{
	Node* newNode =
		(Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

void Remove(Node* head)
{
	int nodup[100] = { NULL };
	nodup[0] = head->data;
	int l = 1;
	Node* cur = head;

	while (cur->next != NULL) {
		int i = 0;
		printf("%d\n", cur->next->data);
		for (i; i < l; i++) {
			if (cur->next->data == nodup[i]) {
				Node* tmp = cur->next;
				cur->next = cur->next->next;
				free(tmp);
				break;
			}
		}
		if (i == l) {
			nodup[l++] = cur->next->data;
			cur = cur->next;
		}
	}
}

int main()
{
	int N, list[100];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
	Node* head = NULL;
	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	printList(head);
	Remove(head);
	printList(head);
	return 0;
}