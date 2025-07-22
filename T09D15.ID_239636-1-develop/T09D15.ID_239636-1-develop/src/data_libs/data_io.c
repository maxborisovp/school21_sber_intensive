#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

int input(double **data, int *n) {
    int stop = 1;
    if (scanf("%d", n) == 1 && *n > 0) {
        *data = malloc((*n) * sizeof(double));
        for (int i = 0; i < *n && stop; i++) {
            if (scanf("%lf", &(*data)[i]) != 1) stop = 0;
        }
    } else
        stop = 0;
    return stop;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2lf", data[i]);
        if (i != n - 1) printf(" ");
    }
}
