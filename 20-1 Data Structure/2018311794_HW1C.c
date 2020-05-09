#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100
typedef enum {
	false,
	true
} bool;

typedef struct {
	char small;
	char large;
	// *Variable "operator"
	// used in ConvInfixToPostfixfunction
	char operator;
}Penta_num; 

typedef struct {
	Penta_num items[MAX_STACK];
	int top;
}Stack;

int cvtint(Penta_num n);

Penta_num add(Penta_num b1, Penta_num b2);
Penta_num subtract(Penta_num b1, Penta_num b2);
Penta_num multiply(Penta_num b1, Penta_num b2);
Penta_num division(Penta_num b1, Penta_num b2);

void InitStack(Stack* pstack);
bool IsFull(Stack* pstack);
bool IsEmpty(Stack* pstack);
Penta_num Peek(Stack* pstack);
void Push(Stack* pstack, Penta_num item);
void Pop(Stack* pstack);

void ConvInfixToPostfix(char* exp, char* convExp, int len);
Penta_num EvalPostfix(char* exp, int len);
void print_Penta_num(Penta_num result);

int main() {
	char infix_exp[100];
	char postfix_exp[100];
	Penta_num result;

	scanf("%s", infix_exp);
	ConvInfixToPostfix(infix_exp, postfix_exp, strlen(infix_exp));
	printf("%s\n%s\n", infix_exp, postfix_exp);
	result = EvalPostfix(postfix_exp, strlen(postfix_exp));
	print_Penta_num(result);
	return 0;
}

int cvtint(Penta_num n) {
	int lar, sma;

	if (n.large < 'A')
		lar = n.large - '0';
	else
		lar = n.large - 'A' + 10;

	if (n.small < 'A')
		sma = n.small - '0';
	else
		sma = n.small - 'A' + 10;
	// printf("lar: %d sma: %d\n", lar, sma);
	return  lar * 15 + sma;
}

Penta_num add(Penta_num b1, Penta_num b2) {
	int r = cvtint(b1) + cvtint(b2);
	Penta_num res;
	int lar = r / 15;
	int sma = r % 15;
	if (lar > 9)
		res.large = 55 + lar;
	else
		res.large = 48 + lar;
	if (sma > 9)
		res.small = 55 + sma;
	else
		res.small = 48 + sma;
	return res;
}
Penta_num subtract(Penta_num b1, Penta_num b2) {
	int r = cvtint(b1) - cvtint(b2);
	Penta_num res;
	int lar = r / 15;
	int sma = r % 15;
	if (lar > 9)
		res.large = 55 + lar;
	else
		res.large = 48 + lar;
	if (sma > 9)
		res.small = 55 + sma;
	else
		res.small = 48 + sma;
	return res;
}
Penta_num multiply(Penta_num b1, Penta_num b2) {
	int r = cvtint(b1) * cvtint(b2);
	Penta_num res;
	int lar = r / 15;
	int sma = r % 15;
	if (lar > 9)
		res.large = 55 + lar;
	else
		res.large = 48 + lar;
	if (sma > 9)
		res.small = 55 + sma;
	else
		res.small = 48 + sma;
	return res;
}
Penta_num division(Penta_num b1, Penta_num b2) {
	int r = cvtint(b1) / cvtint(b2);
	Penta_num res;
	int lar = r / 15;
	int sma = r % 15;
	if (lar > 9)
		res.large = 55 + lar;
	else
		res.large = 48 + lar;
	if (sma > 9)
		res.small = 55 + sma;
	else
		res.small = 48 + sma;
	return res;
}

void InitStack(Stack* pstack) {
	pstack->top = -1;
}
bool IsFull(Stack* pstack) {
	return pstack->top == MAX_STACK - 1;
}
bool IsEmpty(Stack* pstack) {
	return pstack->top == -1;
}

Penta_num Peek(Stack* pstack) {
	if (IsEmpty(pstack)) {
		Penta_num a;
		a.operator = '+';
		return a;
	}
	return pstack->items[pstack->top];
}
void Push(Stack* pstack, Penta_num item) {
	if (IsFull(pstack))
		exit(1);
	pstack->items[++(pstack->top)] = item;
}
void Pop(Stack* pstack) {
	if (IsEmpty(pstack))
		exit(1);
	--(pstack->top);
}

void ConvInfixToPostfix(char* exp, char* convExp, int len) {
	Stack t;
	Penta_num tmp;
	InitStack(&t);
	int j = 0;

	for (int i = 0; i < len; i++) {
		if (exp[i] - '0' >= 0) {
			convExp[j++] = exp[i++];
			convExp[j++] = exp[i];
		}
		else {
			tmp.operator = exp[i];
			while (1) {
				if (IsEmpty(&t)) {
					Push(&t, tmp);
					break;
				}
				if (Peek(&t).operator == '+' || Peek(&t).operator == '-') {
					if (tmp.operator == '*' || tmp.operator == '/') {
						Push(&t, tmp);
						break;
					}
					else {
						convExp[j++] = Peek(&t).operator;
						Pop(&t);
						continue;
					}
				}
				else if (tmp.operator == '*' || tmp.operator == '/') {
					Push(&t, tmp);
					break;
				}
				else {
					convExp[j++] = Peek(&t).operator;
					Pop(&t);
					continue;
				}
			}
		}
	}
	while (!IsEmpty(&t)) {
		convExp[j++] = Peek(&t).operator;
		Pop(&t);
	}
	convExp[j] = '\0';
}
Penta_num EvalPostfix(char* exp, int len) {
	Stack t;
	Penta_num tmp, n1, n2;
	InitStack(&t);
	for (int i = 0; i < len; i++) {
		if (exp[i] - '0' >= 0) {
			tmp.large = exp[i++];
			tmp.small = exp[i];
			Push(&t, tmp);
			// printf("====%c%c====\n", Peek(&t).large, Peek(&t).small);
		}
		else {
			n2 = Peek(&t);
			Pop(&t);
			n1 = Peek(&t);
			Pop(&t);
			if (exp[i] == '*')
				Push(&t, multiply(n1, n2));
			else if (exp[i] == '+')
				Push(&t, add(n1, n2));
			else if (exp[i] == '-')
				Push(&t, subtract(n1, n2));
			else if (exp[i] == '/')
				Push(&t, division(n1, n2));
		}
	}
	return Peek(&t);
}

void print_Penta_num(Penta_num result) {
	printf("%c%c", result.large, result.small);
}