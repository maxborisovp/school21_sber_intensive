#include <stdio.h>
#include <stdlib.h>
#define MMAX 100
#define NMAX 100
int input_stat(int a[MMAX][NMAX], int *m, int *n);
int input_dyn(int ***a, int *m, int *n, int ch);
void output(int **a, int m, int n);
void output_stat(int a[MMAX][NMAX], int m, int n);
void free_dyn(int **a, int m, int ch);

int main() {
    int **data = NULL;
    int data_stat[MMAX][NMAX];
    int n, m;
    int vybor;
    int flag = 0;
    if (scanf("%d", &vybor) == 1 && (vybor == 1 || vybor == 2 || vybor == 3 || vybor == 4)) {
        if (vybor == 1) {
            if (input_stat(data_stat, &m, &n) != -1)
                output_stat(data_stat, m, n);
            else
                flag = 1;
        } else {
            if (input_dyn(&data, &m, &n, vybor) == -1) flag = 1;
            if (flag != 1) {
                output(data, m, n);
            }
            if (data != NULL) free_dyn(data, m, vybor);
        }
    } else
        flag = 1;
    if (flag == 1) printf("n/a");
    return 0;
}

int input_stat(int a[MMAX][NMAX], int *m, int *n) {
    int stop = 0;
    if (scanf("%d %d", m, n) == 2 && *m > 0 && *n > 0 && *m <= MMAX && *n <= NMAX) {
        for (int i = 0; i < *m && stop == 0; i++) {
            for (int j = 0; j < *n && stop == 0; j++) {
                if (scanf("%d", &a[i][j]) != 1) stop = -1;
            }
        }
    } else
        stop = -1;
    return stop;
}

int input_dyn(int ***a, int *m, int *n, int ch) {
    int stop = 0;
    if (scanf("%d %d", m, n) == 2 && *m > 0 && *n > 0) {
        switch (ch) {
            case 2:
                *a = malloc((*m) * (*n) * sizeof(int) + (*m) * sizeof(int *));
                int *ptr = (int *)((*a) + (*m));
                for (int i = 0; i < *m; i++) (*a)[i] = ptr + (*n) * i;
                break;
            case 3:
                *a = malloc((*m) * sizeof(int *));
                for (int i = 0; i < *m; i++) (*a)[i] = malloc((*n) * sizeof(int));
                break;
            case 4:
                *a = malloc((*m) * sizeof(int *));
                int *val_ar = malloc((*m) * (*n) * sizeof(int));
                for (int i = 0; i < *m; i++) (*a)[i] = val_ar + (*n) * i;
                break;
        }
        for (int i = 0; i < *m && stop == 0; i++) {
            for (int j = 0; j < *n && stop == 0; j++) {
                if (scanf("%d", &(*a)[i][j]) != 1) stop = -1;
            }
        }
    } else
        stop = -1;
    return stop;
}

void output_stat(int a[MMAX][NMAX], int m, int n) {
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

void free_dyn(int **a, int m, int ch) {
    switch (ch) {
        case 2:
            free(a);
            break;
        case 3:
            for (int i = 0; i < m; i++) free(a[i]);
            free(a);
            break;
        case 4:
            free(a[0]);
            free(a);
            break;
    }
}
