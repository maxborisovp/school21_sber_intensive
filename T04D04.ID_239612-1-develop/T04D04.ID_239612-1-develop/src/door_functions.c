#include <math.h>
#include <stdio.h>

double func1(double x);
double func2(double x);
double func3(double x);

int main() {
    double pi = 3.14159265358979323846;
    double x_i = -pi;
    double step_x = 2 * pi / 41;
    for (int i = 0; i < 42; i++) {
        printf("%.7f | %.7f | ", x_i, func1(x_i));
        double y_bernulli = func2(x_i);
        if (y_bernulli > 0)
            printf("%.7f | ", y_bernulli);
        else
            printf("- | ");
        if (x_i == 0)
            printf("-\n");
        else
            printf("%.7f\n", func3(x_i));
        x_i = x_i + step_x;
    }
    return 0;
}

double func1(double x) { return pow(1, 3) / (pow(1, 2) + pow(x, 2)); }

double func2(double x) { return sqrt(sqrt(pow(1, 4) + 4 * pow(x, 2) * pow(1, 2)) - pow(x, 2) - pow(1, 2)); }

double func3(double x) { return 1.0 / pow(x, 2); }
