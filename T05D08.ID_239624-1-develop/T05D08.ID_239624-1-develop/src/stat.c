#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != -1) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != n - 1)
            printf("%d ", a[i]);
        else
            printf("%d\n", a[i]);
    }
}

int max(int *a, int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

int min(int *a, int n) {
    int min = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < min) min = a[i];
    }
    return min;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}
