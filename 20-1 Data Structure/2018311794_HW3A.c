#include <stdio.h>
#include <string.h>
#define MAX 200

typedef enum {
	false,
	true
} bool;

typedef struct {
	int x, y;
	bool used;
} P;

P dP(int x, int y, bool used);

typedef struct {
	int rear, front;
	P Q[MAX];
} nextPathQueue;

nextPathQueue nQ;
int path[10][10][2];
int map[10][10];

void push(P p);
P pop();
int isEmpty();
void findpath(int N, int M);

int main() {
	int N, M;

	scanf("%d %d", &N, &M);
	rewind(stdin);

	int i, j;
	for (i = 0; i < N; i++) {
		char mapinfo[11];
		scanf("%s", mapinfo);
		for (j = 0; j < M; j++)
			map[i][j] = mapinfo[j] - '0';
	}
	rewind(stdin);

	nQ.front = 0;
	nQ.rear = 0;
	findpath(N, M);

	int rn = path[N - 1][M - 1][0];
	int rw = path[N - 1][M - 1][1];
	int r = 0;

	if (rn != 0 && rw != 0) {
		r = (rn < rw) ? rn : rw;
	}
	else if (rn == 0) {
		r = rw;;
	}
	else if (rw == 0) {
		r = rn;
	}
	if (!r) r = -1;

	printf("%d\n", r);

	return 0;
}

P dP(int x, int y, bool used) {
	P p = { x, y, used };
	return p;
}

void push(P p) {
	nQ.rear = (nQ.rear + 1) % MAX;
	nQ.Q[nQ.rear] = p;
}

P pop() {
	// P p = nQ.Q[nQ.front];
	nQ.front = (nQ.front + 1) % MAX;
	return nQ.Q[nQ.front];
}

int isEmpty() {
	return nQ.front == nQ.rear;
}

void findpath(int N, int M) {
	push(dP(0, 0, false));
	int dir[5] = { 0, 1, 0, -1, 0 };
	int j = 0, k = 0;
	for (j; j < M; j++) {
		for (k; k < N; k++) {
			path[j][k][0] = 0;
			path[j][k][1] = 0;
		}
	}
	path[0][0][0] = 1;
	path[0][0][1] = 1;
	int nx, ny;
	int i;

	while (!isEmpty()) {
		P p = pop();
		// printf("%d %d ==\n", p.x, p.y);
		int x = p.x;
		int y = p.y;
		for (i = 0; i < 4; i++) {
			nx = x + dir[i];
			ny = y + dir[i+1];
			if (nx >= 0 && ny >= 0 && nx < N && ny < M) {
				if (map[nx][ny] == 0) {
					if (p.used == false) {
						if (path[nx][ny][0] == 0 || path[nx][ny][0] > path[x][y][0] + 1) {
							path[nx][ny][0] = path[x][y][0] + 1;
							// printf("== %d %d \n", dP(nx, ny, false).x, dP(nx, ny, false).y);
							push(dP(nx, ny, false));
						}
					}
					else if (path[nx][ny][1] == 0 || path[nx][ny][1] > path[x][y][1] + 1) {
						path[nx][ny][1] = path[x][y][1] + 1;
						// printf("== %d %d =\n", dP(nx, ny, true).x, dP(nx, ny, true).y);
						push(dP(nx, ny, true));
					}
				}
				else {
					if (p.used == false) {
						if (path[nx][ny][1] == 0 || path[nx][ny][1] > path[x][y][0] + 1) {
							path[nx][ny][1] = path[x][y][0] + 1;
							// printf("== %d %d ==\n", dP(nx, ny, true).x, dP(nx, ny, true).y);
							push(dP(nx, ny, true));
						}
					}
				}
			}
		}
		// printf("=====%d=====\n", isEmpty());
	}
}