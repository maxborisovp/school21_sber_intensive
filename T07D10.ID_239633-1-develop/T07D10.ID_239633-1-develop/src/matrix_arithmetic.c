#include <stdio.h>
#include <stdlib.h>

int input(int ***a, int *m, int *n);
void output(int **a, int m, int n);
void free_dyn(int **a, int m);
int sum(int **matrix_first, int m_first, int n_first, int **matrix_second, int m_second, int n_second,
        int ***matrix_result, int *m_result, int *n_result);
void transpose(int **matrix, int m, int n, int ***matrix_result, int *m_result, int *n_result);
int mul(int **matrix_first, int m_first, int n_first, int **matrix_second, int m_second, int n_second,
        int ***matrix_result, int *m_result, int *n_result);

int main() {
    int **data1 = NULL;
    int **data2 = NULL;
    int **res = NULL;
    int n1, m1, n2, m2, n_res, m_res;
    int vybor;
    int flag = 0;
    if (scanf("%d", &vybor) == 1 && (vybor == 1 || vybor == 2 || vybor == 3)) {
        if (input(&data1, &m1, &n1) == -1) flag = 1;
        if (flag != 1 && (vybor == 1 || vybor == 2)) {
            if (input(&data2, &m2, &n2) == -1) flag = 1;
        }
        if (flag != 1) {
            if (vybor == 1) {
                if (sum(data1, m1, n1, data2, m2, n2, &res, &m_res, &n_res) == 0) flag = 1;
            } else if (vybor == 2) {
                if (mul(data1, m1, n1, data2, m2, n2, &res, &m_res, &n_res) == 0) flag = 1;
            } else if (vybor == 3) {
                transpose(data1, m1, n1, &res, &m_res, &n_res);
            }
        }
        if (flag != 1) output(res, m_res, n_res);
        if (data1 != NULL) free_dyn(data1, m1);
        if (data2 != NULL) free_dyn(data2, m2);
        if (res != NULL) free_dyn(res, m_res);

    } else
        flag = 1;
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

int sum(int **matrix_first, int m_first, int n_first, int **matrix_second, int m_second, int n_second,
        int ***matrix_result, int *m_result, int *n_result) {
    if (m_first == m_second && n_first == n_second) {
        *m_result = m_first;
        *n_result = n_first;
    } else
        return 0;

    *matrix_result = malloc((*m_result) * sizeof(int *));
    for (int i = 0; i < *m_result; i++) (*matrix_result)[i] = malloc((*n_result) * sizeof(int));

    for (int i = 0; i < *m_result; i++) {
        for (int j = 0; j < *n_result; j++) {
            (*matrix_result)[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 1;
}

void transpose(int **matrix, int m, int n, int ***matrix_result, int *m_result, int *n_result) {
    *n_result = m;
    *m_result = n;
    *matrix_result = malloc((*m_result) * sizeof(int *));
    for (int i = 0; i < *m_result; i++) (*matrix_result)[i] = malloc((*n_result) * sizeof(int));

    for (int i = 0; i < *m_result; i++) {
        for (int j = 0; j < *n_result; j++) {
            (*matrix_result)[i][j] = matrix[j][i];
        }
    }
}

int mul(int **matrix_first, int m_first, int n_first, int **matrix_second, int m_second, int n_second,
        int ***matrix_result, int *m_result, int *n_result) {
    if (n_first == m_second) {
        *m_result = m_first;
        *n_result = n_second;
    } else
        return 0;
    *matrix_result = malloc((*m_result) * sizeof(int *));
    for (int i = 0; i < *m_result; i++) (*matrix_result)[i] = malloc((*n_result) * sizeof(int));

    for (int i = 0; i < *m_result; i++) {
        for (int j = 0; j < *n_result; j++) {
            (*matrix_result)[i][j] = 0;
            for (int k = 0; k < n_first; k++) {
                (*matrix_result)[i][j] += matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    return 1;
}
