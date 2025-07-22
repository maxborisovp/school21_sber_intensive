#include <stdio.h>

int sum(int a, int b);
int diff(int a, int b);
int mult(int a, int b);
int divid(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) == 2) {
        printf("%d %d %d ", sum(a, b), diff(a, b), mult(a, b));
        if (b == 0)
            printf("n/a\n");
        else
            printf("%d\n", divid(a, b));
    } else {
        printf("n/a\n");
    }
    return 0;
}

int sum(int a, int b) { return a + b; }

int diff(int a, int b) { return a - b; }

int mult(int a, int b) { return a * b; }

int divid(int a, int b) { return a / b; }
