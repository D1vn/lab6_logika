#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

#define MAXV 100

void print_matrix(int n, int mat[MAXV][MAXV]) {
    printf("Матрица смежности (%d вершин):\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void print_adj_list(int n, int mat[MAXV][MAXV]) {
    printf("Списки смежности:\n");
    for (int i = 0; i < n; i++) {
        printf("v%d: ", i + 1);
        for (int j = 0; j < n; j++)
            if (mat[i][j]) printf("v%d ", j + 1);
        printf("\n");
    }
}

void generate_graph(int n, int mat[MAXV][MAXV], double p) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) mat[i][j] = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((double)rand() / RAND_MAX < p)
                mat[i][j] = mat[j][i] = 1;
}

void identify(int n, int mat[MAXV][MAXV], int u, int v, int* nn, int res[MAXV][MAXV]) {
    if (u == v) { printf("Вершины должны быть различны!\n"); *nn = -1; return; }
    int map[MAXV], idx = 0;
    for (int i = 0; i < n; i++) map[i] = (i == u || i == v) ? -1 : idx++;
    int z = idx, total = idx + 1;

    for (int i = 0; i < total; i++)
        for (int j = 0; j < total; j++) res[i][j] = 0;

    for (int i = 0; i < n; i++) {
        if (map[i] == -1) continue;
        for (int j = 0; j < n; j++) {
            if (map[j] == -1) continue;
            if (mat[i][j]) res[map[i]][map[j]] = 1;
        }
    }
    for (int w = 0; w < n; w++) {
        if (map[w] == -1) continue;
        if (mat[w][u] || mat[w][v]) {
            res[map[w]][z] = 1;
            res[z][map[w]] = 1;
        }
    }
    *nn = total;
}

void contract(int n, int mat[MAXV][MAXV], int u, int v, int* nn, int res[MAXV][MAXV]) {
    if (u == v || mat[u][v] == 0) {
        printf("Ребра между вершинами нет!\n");
        *nn = -1; return;
    }
    identify(n, mat, u, v, nn, res);
}

void split(int n, int mat[MAXV][MAXV], int v, int* nn, int res[MAXV][MAXV]) {
    int total = n + 1, w = n;
    for (int i = 0; i < total; i++)
        for (int j = 0; j < total; j++) res[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != v && j != v) res[i][j] = mat[i][j];

    for (int i = 0; i < n; i++)
        if (i != v && mat[v][i]) {
            res[w][i] = 1;
            res[i][w] = 1;
        }
    res[v][w] = res[w][v] = 1;
    *nn = total;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int n;
    printf("Введите число вершин: ");
    scanf_s("%d", &n);
    if (n <= 0 || n > MAXV) { printf("Неверное число!\n"); return 1; }

    int G1[MAXV][MAXV], G2[MAXV][MAXV];
    generate_graph(n, G1, 0.3);
    generate_graph(n, G2, 0.3);

    printf("\n G1 \n");
    print_matrix(n, G1); print_adj_list(n, G1);
    printf("\n G2 \n");
    print_matrix(n, G2); print_adj_list(n, G2);

    int g, op, u, v, nn;
    int res[MAXV][MAXV];

    while (1) {
        printf("\nГраф (1-G1, 2-G2, 0-выход): ");
        scanf_s("%d", &g);
        if (g == 0) break;
        if (g != 1 && g != 2) { printf("Неверно!\n"); continue; }

        int (*G)[MAXV] = (g == 1) ? G1 : G2;

        printf("Операция (1-отожд., 2-стягивание, 3-расщепление): ");
        scanf_s("%d", &op);

        if (op == 1) {
            printf("Вершины u v: ");
            scanf_s("%d %d", &u, &v);
            identify(n, G, u - 1, v - 1, &nn, res);
        }
        else if (op == 2) {
            printf("Вершины u v: ");
            scanf_s("%d %d", &u, &v);
            contract(n, G, u - 1, v - 1, &nn, res);
        }
        else if (op == 3) {
            printf("Вершина v: ");
            scanf_s("%d", &v);
            split(n, G, v - 1, &nn, res);
        }
        else {
            printf("Неверная операция!\n");
            continue;
        }

        if (nn > 0) {
            printf("\nРезультат:\n");
            print_matrix(nn, res);
            print_adj_list(nn, res);
        }
    }
    return 0;
}