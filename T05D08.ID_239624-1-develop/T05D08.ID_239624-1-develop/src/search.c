/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int *a, int n, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != -1) {
        output_result(data, n, mean(data, n), variance(data, n));
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *n) {
    int stop = 0;
    if (scanf("%d", n) == 1 && *n > 0 && *n <= NMAX) {
        for (int i = 0; i < *n && stop == 0; i++) {
            if (scanf("%d", &a[i]) != 1) stop = -1;
        }
    } else
        stop = -1;
    return stop;
}

double mean(int *a, int n) {
    double mean_sum = 0;
    for (int i = 0; i < n; i++) {
        mean_sum = mean_sum + a[i];
    }
    return mean_sum / n;
}

double variance(int *a, int n) {
    double mean_a = mean(a, n);
    double var_sum = 0;
    for (int i = 0; i < n; i++) {
        var_sum = var_sum + (a[i] - mean_a) * (a[i] - mean_a);
    }
    return var_sum / n;
}

void output_result(int *a, int n, double mean_v, double variance_v) {
    int stop = 0;
    for (int i = 0; i < n && stop == 0; i++) {
        if (a[i] % 2 == 0 && a[i] >= mean_v && a[i] <= mean_v + 3 * sqrt(variance_v) && a[i] != 0) {
            stop = 1;
            printf("%d", a[i]);
        }
    }
    if (stop == 0) printf("0");
}
