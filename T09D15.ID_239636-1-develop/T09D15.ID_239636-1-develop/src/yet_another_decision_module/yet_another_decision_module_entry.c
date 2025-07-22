#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data = NULL;
    int n;
    int flag = 1;
    flag = flag && input(&data, &n);
    if (flag) {
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
    } else
        printf("n/a");
    free(data);
    return 0;
}
