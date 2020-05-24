#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int pr;
    char o;
} operand;

typedef struct _Node{
    operand oper;
    int data;
    struct _Node* left, *right;
} Node;

typedef struct {
	int top;
	Node node[100];
} nStack;

typedef struct {
    int top;
	operand oper[100];
} oStack;

nStack np;
oStack op;
Node tmpNode = { NULL,NULL,NULL };

Node dno(int data);
operand dop(int pr, char op);
void Npush(int n);
void Nodepush(Node node);
void Opush(operand o);
Node Npop();
operand Opop();
Node Npeek();
operand Opeek();

Node* opTree(Node* head);
int result(Node* head, int i);

int main() {
	char ar[10];
	char buf='a';
    int M, P;
    Node* arithNode = NULL;

    buf = getchar();
	while (buf != '\n') {
        // printf("---%c---\n", buf);
        int num = 0;

        if (buf == '\n')
            break;
        else if (buf >= '0' && buf <= '9') {
            while (buf >= '0' && buf <= '9') {
                num = num * 10 + (buf - '0');
                buf = getchar();
            }
            Npush(num);
        }
        else if (buf == 'x') {
            Npush(99999);
            buf = getchar();
        }
        else if (buf == '(') {
            Opush(dop(0, buf));
            buf = getchar();
        }
        else if (buf == ')') {
            while (Opeek().o != '(')
                arithNode = opTree(arithNode);
            Opop();
            buf = getchar();
        }        
        else if (buf == '*' || buf == '+' || buf == '-') {
            int pr = 0;
            if (buf == '*')
                pr = 2;
            else if (buf == '+')
                pr = 1;
            else if (buf == '-')
                pr = 1;
            while (op.top != 0 && pr <= Opeek().pr) 
                arithNode = opTree(arithNode);
            Opush(dop(pr, buf));
            buf = getchar();
        }
	}
    // printf("v^v^v^v^[Leftover]^v^v^v^v^v\n");
    while (op.top!=0)
        arithNode = opTree(arithNode);
    scanf("%d %d", &P, &M);
    int i;
    for (i = 0; i < 10; i++) {
        // printf("\n\n[Executing calculation] i : %d\n", i);
        int res = result(arithNode, i);
        // printf("[res] %d\n", res);
        if (res % M == P) {
            printf("%d", i);
            break;
        }
    }
    return 0;
}

Node dno(int data) {
    // printf("[dno] data : %d\n", data);
    Node node;
    node.data = data;
    return node;
}

operand dop(int pr, char op) {
    // printf("[dop] pr : %d | op : %c\n", pr, op);
    operand o = { pr, op };
    return o;
}

void Npush(int n) {
    // printf("[Npush] data : %d\n", n);
    Node node;
    node.data = n;
    node.left = NULL;
    node.right = NULL;
    node.oper.o = NULL;
    np.top++;
    np.node[np.top] = node;
}

void Nodepush(Node node) {
    // printf("[Nodepush] data : %d | oper : %c\n", node.data==NULL?88888:node.data, node.oper.o);
    np.top++;
    np.node[np.top] = node;
}

void Opush(operand o) {
    // printf("[Opush] oper : %c\n", o.o);
    op.top++;
    op.oper[op.top] = o;
}

Node Npop() {
	Node node = Npeek();
	np.top--;
    /* printf("[Npop] peek & poped : %d | %c\n",
        node.data==NULL?88888:node.data,
        node.oper.o==NULL?'!':node.oper.o);
	*/
    return node;
}

operand Opop() {
	operand o = Opeek();
    op.top--;
    // printf("[Opop] peek & poped : %c\n", o.o);
	return o;
}

Node Npeek() {
    /*
    printf("[Npeek] data : %d | oper : %c\n",
        np.node[np.top].data == NULL ? 88888 : np.node[np.top].data,
        np.node[np.top].oper.o == NULL ? '!' : np.node[np.top].oper.o);
    */
    return np.node[np.top];
}

operand Opeek() {
    // printf("[Opeek] oper : %c\n", op.oper[op.top].o);
    return op.oper[op.top];
}

Node* opTree(Node* head) {
    // printf("=\n[Executing tree]-------------------------------------\n=\n");
    Node* newNode = (Node*)malloc(sizeof(Node));
    Node* firstNode = (Node*)malloc(sizeof(Node));
    Node* secondNode = (Node*)malloc(sizeof(Node));

    Node a = Npop();
    Node b = Npop();
    operand oper = Opop();
    
    *firstNode = a;
    *secondNode = b;
    /*
    if (firstNode->left == NULL)
        printf("D===========%d===%d===========\n", firstNode->data, secondNode->data);
    else if(firstNode->oper.o != NULL)
        printf("T===========%c===%d===========\n", firstNode->oper.o, secondNode->data);
    */
    if (firstNode->oper.o == NULL) {
        newNode->left = secondNode;
        newNode->right = firstNode;
    }
    else {
        newNode->left = firstNode;
        newNode->right = secondNode;
    }
    newNode->oper = oper;
    newNode->data = NULL;
    head = newNode;

    Nodepush(*head);

    // printf("=\n[Executed tree]--------------------------------------\n=\n");
    return head;
}

int result(Node* node, int i) {
    int dat = 0;
    if (node->left==NULL) {
        // printf("[LEFT-MOST NODE]\n");
        if (node->data == 99999)
            dat = i;
        else
            dat = node->data;
        // printf("[TEST] ===%d===\n", dat);
        return dat;
    }
    else {
        int l = result(node->left, i);
        int r = -999999;
        if (node->right->data == 99999)
            r = i;
        else
            r = node->right->data;
        // printf("[node->oper] %c\n", node->oper.o);
        if (node->oper.o == '*')
            dat = l * r;
        else if (node->oper.o == '+')
            dat = l + r;
        else if (node->oper.o == '-')
            dat = l - r;
        // printf("[dat] l : %d | r : %d | dat : %d |\n", l, r, dat);
  	return dat;
    }
}
