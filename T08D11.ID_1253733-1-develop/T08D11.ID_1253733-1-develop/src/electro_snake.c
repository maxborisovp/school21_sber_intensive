#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);
int input(int ***a, int *m, int *n);
void output(int **a, int m, int n);
void free_dyn(int **a, int m);
void sort_buble(int *a, int n);

int main() {
    int **matrix = NULL;
    int **result = NULL;
    int n, m;
    int flag = 0;
    if (input(&matrix, &m, &n) != -1) {
        result = malloc(m * sizeof(int *));
        for (int i = 0; i < m; i++) result[i] = malloc(n * sizeof(int));
        sort_vertical(matrix, m, n, result);
        output(result, m, n);
        printf("\n");
        sort_horizontal(matrix, m, n, result);
        output(result, m, n);
        free_dyn(result, m);
    } else
        flag = 1;
    if (matrix != NULL) free_dyn(matrix, m);
    if (flag == 1) printf("n/a");
    return 0;
}

int input(int ***a, int *m, int *n) {
    int stop = 0;
    if (scanf("%d %d", m, n) == 2 && *m > 0 && *n > 0) {
        *a = malloc((*m) * sizeof(int *));
        for (int i = 0; i < *m; i++) (*a)[i] = malloc((*n) * sizeof(int));

        for (int i = 0; i < *m && stop == 0; i++) {
            for (int j = 0; j < *n && stop == 0; j++) {
                if (scanf("%d", &(*a)[i][j]) != 1) stop = -1;
            }
        }
    } else
        stop = -1;
    return stop;
}

void output(int **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", a[i][j]);
            if (j != n - 1)
                printf(" ");
            else if (j == n - 1 && i != m - 1)
                printf("\n");
        }
    }
}

void free_dyn(int **a, int m) {
    for (int i = 0; i < m; i++) free(a[i]);
    free(a);
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int *a = malloc(n * m * sizeof(int));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[k] = matrix[i][j];
            k++;
        }
    }
    sort_buble(a, n * m);

    k = 0;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (j % 2 == 0)
                result_matrix[i][j] = a[k];
            else
                result_matrix[n - 1 - i][j] = a[k];
            k++;
        }
    }
    free(a);
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int *a = malloc(n * m * sizeof(int));
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[k] = matrix[i][j];
            k++;
        }
    }
    sort_buble(a, n * m);
    k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0)
                result_matrix[i][j] = a[k];
            else
                result_matrix[i][m - 1 - j] = a[k];
            k++;
        }
    }
    free(a);
}

void sort_buble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j + 1] < a[j]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}
