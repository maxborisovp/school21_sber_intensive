#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data = NULL;
    int n;
    int flag = 1;
    // Don`t forget to allocate memory !

    flag = flag && input(&data, &n);
    if (flag) {
        if (normalization(data, n))
            output(data, n);
        else
            printf("ERROR");
    } else
        printf("n/a");
    free(data);

    return 0;
}
