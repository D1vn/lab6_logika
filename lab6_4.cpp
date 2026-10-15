#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX 20
#define MAXP 400

void generate(int n, int m[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 2)
                m[i][j] = m[j][i] = 1;
}

void print(int n, int m[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n1, n2;
    printf("Введите размеры G1 и G2 (n1 n2): ");
    scanf("%d %d", &n1, &n2);

    if (n1 <= 0 || n2 <= 0 || n1 > MAX || n2 > MAX) {
        printf("Недопустимые размеры!\n");
        return 1;
    }

    int G1[MAX][MAX], G2[MAX][MAX];
    generate(n1, G1);
    generate(n2, G2);

    printf("\nG1:\n");
    print(n1, G1);

    printf("\nG2:\n");
    print(n2, G2);

    int N = n1 * n2;
    int P[MAXP][MAXP] = { 0 };

    for (int i = 0; i < n1; i++) {
        for (int k = 0; k < n2; k++) {
            int a = i * n2 + k;
            for (int j = 0; j < n1; j++) {
                for (int l = 0; l < n2; l++) {
                    int b = j * n2 + l;
                    if (a == b) continue;

                    if ((i == j && G2[k][l]) || (k == l && G1[i][j]))
                        P[a][b] = 1;
                }
            }
        }
    }

    printf("\nG1 x G2 (%d вершин):\n", N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", P[i][j]);
        printf("\n");
    }

    return 0;
}