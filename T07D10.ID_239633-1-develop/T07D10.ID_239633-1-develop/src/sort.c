#include <stdio.h>
#include <stdlib.h>

int input(int **a, int *n);
void output(int *a, int n);
void sort_buble(int *a, int n);

int main() {
    int *data = NULL;
    int n;
    if (input(&data, &n) != -1) {
        sort_buble(data, n);
        output(data, n);

    } else {
        printf("n/a");
    }
    free(data);
    return 0;
}

int input(int **a, int *n) {
    int stop = 0;
    if (scanf("%d", n) == 1 && *n > 0) {
        *a = malloc((*n) * sizeof(int));
        for (int i = 0; i < *n && stop == 0; i++) {
            if (scanf("%d", &(*a)[i]) != 1) stop = -1;
        }
    } else
        stop = -1;
    return stop;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
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
