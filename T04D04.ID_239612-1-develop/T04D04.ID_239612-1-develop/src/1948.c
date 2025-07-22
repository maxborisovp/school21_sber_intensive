#include <stdio.h>

int gr_prime_div(int a);
int rem_of_div(int a, int b);

int main() {
    int a;
    if (scanf("%d", &a) == 1 && a != 0 && a != 1 && a != -1) {
        if (a < 0) a = -a;
        printf("%d", gr_prime_div(a));
    } else {
        printf("n/a");
    }
    return 0;
}

int gr_prime_div(int a) {
    int nod = a;
    int div_of_nod;
    while (nod > 1) {
        if (rem_of_div(a, nod) == 0) {
            div_of_nod = nod - 1;
            while (div_of_nod != 1) {
                if (rem_of_div(nod, div_of_nod) == 0) break;
                div_of_nod--;
            }
        }
        if (div_of_nod != 1)
            nod--;
        else
            break;
    }
    return nod;
}

int rem_of_div(int a, int b) {
    while (a >= b) {
        a = a - b;
    }
    return a;
}
