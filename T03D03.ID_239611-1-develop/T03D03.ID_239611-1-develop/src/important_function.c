#include <math.h>
#include <stdio.h>

float func_y(float x);

int main() {
    float x;
    if (scanf("%f", &x) == 1 && x > 0) {
        printf("%.1f\n", func_y(x));
    } else {
        printf("n/a\n");
    }
    return 0;
}

float func_y(float x) {
    float y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3) - 1e3) * x + 3) / (x * x / 2.0) -
              x * pow((10 + x), (2.0 / x)) - 1.01;
    return y;
}
