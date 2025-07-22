#include <stdio.h>
#include <stdlib.h>
int input(int ***a, int *m, int *n, int ch);
void output(int **a, int m, int n);
void output_n(int *a, int n);
void free_dyn(int **a, int m, int ch);
int sum_n(int *a, int n);
void sort_buble(int **a, int m, int n);

int main() {
    int **data = NULL;
    int n, m;
    int vybor;
    int flag = 0;
    if (scanf("%d", &vybor) == 1 && (vybor == 1 || vybor == 2 || vybor == 3)) {
        if (input(&data, &m, &n, vybor) == -1) flag = 1;
        if (flag != 1) {
            sort_buble(data, m, n);
            output(data, m, n);
        }
        if (data != NULL) free_dyn(data, m, vybor);
    } else
        flag = 1;
    if (flag == 1) printf("n/a");
    return 0;
}

int input(int ***a, int *m, int *n, int ch) {
    int stop = 0;
    if (scanf("%d %d", m, n) == 2 && *m > 0 && *n > 0) {
        switch (ch) {
            case 1:
                *a = malloc((*m) * (*n) * sizeof(int) + (*m) * sizeof(int *));
                int *ptr = (int *)((*a) + (*m));
                for (int i = 0; i < *m; i++) (*a)[i] = ptr + (*n) * i;
                break;
            case 2:
                *a = malloc((*m) * sizeof(int *));
                for (int i = 0; i < *m; i++) (*a)[i] = malloc((*n) * sizeof(int));
                break;
            case 3:
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

void output_n(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
}

void free_dyn(int **a, int m, int ch) {
    switch (ch) {
        case 1:
            free(a);
            break;
        case 2:
            for (int i = 0; i < m; i++) free(a[i]);
            free(a);
            break;
        case 3:
            if (m > 0) free(a[0]);
            free(a);
            break;
    }
}

int sum_n(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

void sort_buble(int **a, int m, int n) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (sum_n(a[j + 1], n) < sum_n(a[j], n)) {
                int *tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}
