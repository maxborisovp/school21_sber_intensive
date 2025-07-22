#include <stdio.h>

int fibbonachi(int n);

int main() {
    int n;
    if (scanf("%d", &n) == 1 && n > 0) {
        printf("%d", fibbonachi(n));
    } else {
        printf("n/a");
    }
    return 0;
}

int fibbonachi(int n) {
    if (n == 1 || n == 2)
        return 1;
    else
        return fibbonachi(n - 1) + fibbonachi(n - 2);
}
