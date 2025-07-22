#include <stdio.h>
#include <stdlib.h>

#ifdef USE_DYN
#include <dlfcn.h>
#else
#include "../data_module/data_process.h"
#endif

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "../yet_another_decision_module/decision.h"

int main() {
    double *data = NULL;
    int n;
    int flag = 1;

    printf("LOAD DATA...\n");
    flag = flag && input(&data, &n);

#ifdef USE_DYN
    if (flag) {
        printf("RAW DATA:\n\t");
        output(data, n);

        printf("\nNORMALIZED DATA:\n\t");
        void *dlib = dlopen("./libdata_process.so", RTLD_LAZY);
        if (!dlib)
            printf("n/a");
        else {
            int (*normalization)(double *, int) = (int (*)(double *, int))dlsym(dlib, "normalization");
        }
        if (normalization(data, n)) {
            output(data, n);
            printf("\nSORTED NORMALIZED DATA:\n\t");
            sort(data, n);
            output(data, n);
            printf("\nFINAL DECISION:\n\t");

            if (make_decision(data, n)) {
                printf("YES");
            } else
                printf("NO");
        } else
            printf("ERROR");
        dlclose(dlib);
    } else
        printf("n/a");
    free(data);
#else
    if (flag) {
        printf("RAW DATA:\n\t");
        output(data, n);

        printf("\nNORMALIZED DATA:\n\t");
        if (normalization(data, n)) {
            output(data, n);
            printf("\nSORTED NORMALIZED DATA:\n\t");
            sort(data, n);
            output(data, n);
            printf("\nFINAL DECISION:\n\t");

            if (make_decision(data, n)) {
                printf("YES");
            } else
                printf("NO");

        }

        else
            printf("ERROR");
    } else
        printf("n/a");
    free(data);
#endif
    return 0;
}
