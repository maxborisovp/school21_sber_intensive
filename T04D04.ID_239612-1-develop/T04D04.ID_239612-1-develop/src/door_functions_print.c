#include <math.h>
#include <stdio.h>

double func1(double x);
double func2(double x);
double func3(double x);
void print_f1();
void print_f2();
void print_f3();

int main() {
    print_f1();
    printf("==========================================\n");
    print_f2();
    printf("==========================================\n");
    print_f3();
    printf("==========================================\n");
    return 0;
}

double func1(double x) { return pow(1, 3) / (pow(1, 2) + pow(x, 2)); }

double func2(double x) { return sqrt(sqrt(pow(1, 4) + 4 * pow(x, 2) * pow(1, 2)) - pow(x, 2) - pow(1, 2)); }

double func3(double x) { return 1.0 / pow(x, 2); }

void print_f1() {
    double pi = 3.14159265358979323846;
    double x_i, y_i, y1;
    double step_x = 2.0 * pi / 41;
    double y_max, y_min, step_y;
    x_i = -pi;
    y_max = func1(x_i);
    y_min = func1(x_i);
    for (int j = 0; j < 42; j++) {
        y1 = func1(x_i);
        if (y_max < y1) y_max = y1;
        if (y_min > y1) y_min = y1;
        x_i = x_i + step_x;
    }
    step_y = -(y_max - y_min) / 20;
    y_i = y_max;
    for (int i = 0; i < 21; i++) {
        x_i = -pi;
        for (int j = 0; j < 42; j++) {
            y1 = func1(x_i);
            if (fabs(y1 - y_i) <= -step_y / 2)
                printf("*");
            else
                printf(" ");
            x_i = x_i + step_x;
        }
        y_i = y_i + step_y;
        printf("\n");
    }
}

void print_f2() {
    double pi = 3.14159265358979323846;
    double x_i, y_i, y2;
    double step_x = 2.0 * pi / 41;
    double y_max, y_min, step_y;
    x_i = -pi;
    y_max = 0;
    y_min = 0;
    for (int j = 0; j < 42; j++) {
        y2 = func2(x_i);
        if (y_max < y2) y_max = y2;
        if (y_min > y2) y_min = y2;
        x_i = x_i + step_x;
    }
    step_y = -(y_max - y_min) / 20;
    y_i = y_max;
    for (int i = 0; i < 21; i++) {
        x_i = -pi;
        for (int j = 0; j < 42; j++) {
            y2 = func2(x_i);
            if (fabs(y2 - y_i) <= -step_y / 2)
                printf("*");
            else
                printf(" ");
            x_i = x_i + step_x;
        }
        y_i = y_i + step_y;
        printf("\n");
    }
}
void print_f3() {
    double pi = 3.14159265358979323846;
    double x_i, y_i, y3;
    double step_x = 2.0 * pi / 41;
    double y_max, y_min, step_y;
    x_i = -pi;
    y_max = func3(x_i);
    y_min = func3(x_i);
    for (int j = 0; j < 42; j++) {
        y3 = func3(x_i);
        if (y_max < y3) y_max = y3;
        if (y_min > y3) y_min = y3;
        x_i = x_i + step_x;
    }
    step_y = -(y_max - y_min) / 20;
    y_i = y_max;
    for (int i = 0; i < 21; i++) {
        x_i = -pi;
        for (int j = 0; j < 42; j++) {
            y3 = func3(x_i);
            if (fabs(y3 - y_i) <= -step_y / 2)
                printf("*");
            else
                printf(" ");
            x_i = x_i + step_x;
        }
        y_i = y_i + step_y;
        printf("\n");
    }
}
