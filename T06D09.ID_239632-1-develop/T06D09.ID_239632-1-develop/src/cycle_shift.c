#include <stdio.h>
#define NMAX 10

int input(int *a, int *n, int *shift);
void output(int *a, int n);
void arr_shift_l(int *a, int n);
void arr_shift_r(int *a, int n);
void shift(int *a, int n, int shift);

int main() {
    int n, A[NMAX], c;
    if (input(A, &n, &c) != -1) {
        shift(A, n, c);
        output(A, n);
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *n, int *shift) {
    int stop = 0;
    if (scanf("%d", n) == 1 && *n > 0 && *n <= NMAX) {
        for (int i = 0; i < *n && stop == 0; i++) {
            if (scanf("%d", &a[i]) != 1) stop = -1;
        }
    } else
        stop = -1;
    if (stop == 0 && scanf("%d", shift) != 1) stop = -1;
    return stop;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
}

void arr_shift_r(int *a, int n) {
    int tmp = a[n - 1];
    for (int i = n - 1; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = tmp;
}

void arr_shift_l(int *a, int n) {
    int tmp = a[0];
    for (int i = 0; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    a[n - 1] = tmp;
}

void shift(int *a, int n, int shift) {
    int k = shift;
    if (k < 0) k = -k;
    for (int i = 0; i < k; i++) {
        if (shift > 0) arr_shift_l(a, n);
        if (shift < 0) arr_shift_r(a, n);
    }
}
