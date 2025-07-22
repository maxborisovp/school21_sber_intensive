#include "data_stat.h"

double max(double *data, int n) {
    double max_number = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] > max_number) max_number = data[i];
    }
    return max_number;
}

double min(double *data, int n) {
    double min_number = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] < min_number) min_number = data[i];
    }
    return min_number;
}

double mean(double *data, int n) {
    double mean_sum = 0;
    for (int i = 0; i < n; i++) {
        mean_sum = mean_sum + data[i];
    }
    return mean_sum / n;
}

double variance(double *data, int n) {
    double mean_data = mean(data, n);
    double var_sum = 0;
    for (int i = 0; i < n; i++) {
        var_sum = var_sum + (data[i] - mean_data) * (data[i] - mean_data);
    }
    return var_sum / n;
}

void sort(double *data, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (data[j + 1] < data[j]) {
                double tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}
