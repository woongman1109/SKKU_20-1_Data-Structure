#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	int coeff, exp;
	struct _Node* next;
}Node;

typedef struct {
	Node* tail;
	int len;
} Polynomial;

void printPoly(Polynomial* p) {
	Node* ptr = p->tail->next;
	int i = 0;
	for (i; i < p->len; i++) {
		if(ptr->coeff>0 && i)
			printf("+%dx^%d", ptr->coeff, ptr->exp);
		else
			printf("%dx^%d", ptr->coeff, ptr->exp);
		ptr = ptr->next;
	}
	printf("\n");
}

void insertInit(Polynomial* p, int c, int e) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->coeff = c;
	newNode->exp = e;
	newNode->next = newNode;

	p->tail = newNode;
	p->len++;
}

void pushBack(Polynomial* p, int c, int e) {
	if (!p->len)
		insertInit(p, c, e);
	else {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->coeff = c;
		newNode->exp = e;
		newNode->next = p->tail->next;

		p->tail->next = newNode;
		p->tail = newNode;
		p->len++;
	}
}

int main() {
	int pn[50] = { 0 }, N = 0;
	char num[100] = "";
	
	Node* p1n = NULL;
	Node* p2n = NULL;

	char p1[100] = "", p2[100] = "";
	scanf("%s", p1);
	scanf("%s", p2);

	int i = 0;
	int p = 0;
	while (p1[i]!='\0') {
		int j = i;
		int k = 0;
		while (p1[i] != 'x') {
			num[k++] = p1[i++];
		} num[k] = '\0';
		pn[p++] = atoi(num);
		k = 0;
		i += 2;
		j = i;
		while (p1[i] > 47 && p1[i] < 58) {
			num[k++] = p1[i++];
		} num[k] = '\0';
		pn[p++] = atoi(num);
	}
	Polynomial poly1 = { p1n, 0 };
	for (i = 0; i < p; i+=2)
		pushBack(&poly1, pn[i], pn[i+1]);

	i = 0; p = 0;
	while (p2[i] != '\0') {
		int j = i;
		int k = 0;
		while (p2[i] != 'x') {
			num[k++] = p2[i++];
		} num[k] = '\0';
		pn[p++] = atoi(num);
		k = 0;
		i += 2;
		j = i;
		while (p2[i] > 47 && p2[i] < 58) {
			num[k++] = p2[i++];
		} num[k] = '\0';
		pn[p++] = atoi(num);
	}
	Polynomial poly2 = { p2n, 0 };
	for (i = 0; i < p; i += 2)
		pushBack(&poly2, pn[i], pn[i + 1]);

	p = 0;
	int p1p = 0, p2p = 0;
	p1n = poly1.tail->next;
	p2n = poly2.tail->next;
	while (1) {
		if (p1p == poly1.len && p2p == poly2.len)
			break;
		printf("====\n");
		if (p2p == poly2.len || p1n->exp < p2n->exp) {
			pn[p++] = p1n->coeff;
			pn[p++] = p1n->exp;
			p1n = p1n->next;
			printf("%d %d\n", pn[p - 2], pn[p - 1]);
			p1p++;
		}
		else if (p1p == poly1.len || p1n->exp > p2n->exp) {
			pn[p++] = p2n->coeff;
			pn[p++] = p2n->exp;
			p2n = p2n->next;
			printf("%d %d\n", pn[p - 2], pn[p - 1]);
			p2p++;
		}
		else if (p1n->exp == p1n->exp) {
			pn[p++] = p1n->coeff + p2n->coeff;
			pn[p++] = p1n->exp;
			p1n = p1n->next;
			p2n = p2n->next;
			printf("%d %d\n", pn[p - 2], pn[p - 1]);
			p1p++;
			p2p++;
		} 
	}

	Node* res = NULL;
	Polynomial polyres = { res, 0 };
	for (i = 0; i < p; i += 2)
		pushBack(&polyres, pn[i], pn[i + 1]);

	printPoly(&polyres);

}