#include <stdio.h>

int compare(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) == 2) {
        printf("%d\n", compare(a, b));
    } else {
        printf("n/a\n");
    }
    return 0;
}

int compare(int a, int b) {
    int max;
    if (a >= b)
        max = a;
    else
        max = b;
    return max;
}
