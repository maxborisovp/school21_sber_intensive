#include <stdio.h>

void inSircle(float x, float y);

int main() {
    float x, y;
    if (scanf("%f %f", &x, &y) == 2) {
        inSircle(x, y);
    } else {
        printf("n/a\n");
    }
    return 0;
}

void inSircle(float x, float y) {
    if (x * x + y * y < 25)
        printf("GOTCHA\n");
    else
        printf("MISS\n");
}
