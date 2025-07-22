#include <stdio.h>
#define NMAX 10

int input(int *a, int *b);
void output(int *a);
void sort_quick(int *a, int size);
void heapify(int *a, int n, int i);
void sort_pyramid(int *a, int n);

int main() {
    int mass1[NMAX], mass2[NMAX];
    if (input(mass1, mass2) != -1) {
        sort_quick(mass1, NMAX);
        output(mass1);
        printf("\n");
        sort_pyramid(mass2, NMAX);
        output(mass2);

    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *b) {
    int stop = 0;
    for (int i = 0; i < NMAX && stop == 0; i++) {
        if (scanf("%d", &a[i]) != 1)
            stop = -1;
        else
            b[i] = a[i];
    }
    return stop;
}

void output(int *a) {
    for (int i = 0; i < NMAX; i++) {
        printf("%d", a[i]);
        if (i != NMAX - 1) printf(" ");
    }
}

void sort_quick(int *a, int size) {
    int i = 0;
    int j = size - 1;
    int mid = a[size / 2];

    do {
        while (a[i] < mid) {
            i++;
        }
        while (a[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        sort_quick(a, j + 1);
    }
    if (i < size) {
        sort_quick(&a[i], size - i);
    }
}

void heapify(int *a, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        int tmp = a[i];
        a[i] = a[largest];
        a[largest] = tmp;
        heapify(a, n, largest);
    }
}

void sort_pyramid(int *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);

    for (int i = n - 1; i >= 0; i--) {
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        heapify(a, i, 0);
    }
}
