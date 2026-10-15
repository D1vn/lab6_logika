#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAXV 100   


void print_matrix(int n, int mat[MAXV][MAXV]) {
    printf("Матрица смежности (%d вершин):\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


void print_adj_list(int n, int mat[MAXV][MAXV]) {
    printf("Списки смежности:\n");
    for (int i = 0; i < n; i++) {
        printf("v%d: ", i + 1);
        int first = 1;
        for (int j = 0; j < n; j++) {
            if (mat[i][j]) {
                if (!first) printf(", ");
                printf("v%d", j + 1);
                first = 0;
            }
        }
        printf("\n");
    }
}


void generate_graph(int n, int mat[MAXV][MAXV], double p) {

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX < p) {
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n;
    printf("Введите число вершин для G1 и G2: ");
    scanf_s("%d", &n);

    if (n <= 0 || n > MAXV) {
        printf("Недопустимое число вершин. Допустимо от 1 до %d.\n", MAXV);
        return 1;
    }

    int G1[MAXV][MAXV], G2[MAXV][MAXV];

    generate_graph(n, G1, 0.3);
    generate_graph(n, G2, 0.3);

    printf("\n Граф G1 \n");
    print_matrix(n, G1);
    printf("\n");
    print_adj_list(n, G1);

    printf("\n Граф G2 \n");
    print_matrix(n, G2);
    printf("\n");
    print_adj_list(n, G2);

    return 0;
}