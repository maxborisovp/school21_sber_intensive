#include <stdio.h>
#define NMAX 10

int input(int *a);
void output(int *a);
void sort_buble(int *a);

int main() {
    int data[NMAX];
    if (input(data) != -1) {
        sort_buble(data);
        output(data);
    } else
        printf("n/a");

    return 0;
}

int input(int *a) {
    int stop = 0;
    for (int i = 0; i < NMAX && stop == 0; i++) {
        if (scanf("%d", &a[i]) != 1) stop = -1;
    }
    return stop;
}

void output(int *a) {
    for (int i = 0; i < NMAX; i++) {
        printf("%d", a[i]);
        if (i != NMAX - 1) printf(" ");
    }
}

void sort_buble(int *a) {
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX - 1; j++) {
            if (a[j + 1] < a[j]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}
