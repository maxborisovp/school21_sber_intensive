#include <stdio.h>
#define LEN 100

int input(int *a, int *n);
void output(int *a, int n);
void arr_shift_l(int *a, int n);
void arr_shift_r(int *a, int n);
void add_delete_zeros(int *a, int *n, int shift);
void privedenie_arr(int *buff1, int *len1, int *buff2, int *len2);
int k_zeros(int *a, int n);
void sum(int *buff1, int len1, int *buff2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int *result, int *result_length);

int main() {
    int n1, data1[LEN + 1], n2, data2[LEN + 1], res_n1, res_n2, res1[LEN + 1], res2[LEN + 1];
    res_n1 = res_n2 = 0;
    if (input(data1, &n1) != -1 && input(data2, &n2) != -1) {
        privedenie_arr(data1, &n1, data2, &n2);
        sum(data1, n1, data2, res1, &res_n1);
        sub(data1, n1, data2, res2, &res_n2);
        output(res1, res_n1);
        printf("\n");
        output(res2, res_n2);
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int *n) {
    int stop = 0;
    *n = 0;
    char ch;
    while (stop == 0) {
        if (scanf("%d%c", &a[*n], &ch) != 2 || (ch != ' ' && ch != '\n') || a[*n] > 9 || a[*n] < 0)
            stop = -1;
        else
            *n = *n + 1;
        if (ch == '\n') stop = 1;
    }
    return stop;
}

void output(int *a, int n) {
    if (n == 0)
        printf("n/a");
    else {
        for (int i = 0; i < n; i++) {
            printf("%d", a[i]);
            if (i != n - 1) printf(" ");
        }
    }
}

int k_zeros(int *a, int n) {
    int k = 0;
    for (int i = 0; i < n && a[i] == 0; i++) {
        k++;
    }
    return k;
}

void arr_shift_r(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = 0;
}

void arr_shift_l(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
}

void add_delete_zeros(int *a, int *n, int shift) {
    int k = shift;
    if (k < 0) k = -k;
    for (int i = 0; i < k; i++) {
        if (shift > 0) {
            arr_shift_l(a, *n);
            (*n)--;
        }
        if (shift < 0) {
            (*n)++;
            arr_shift_r(a, *n);
        }
    }
    if (*n == 0) {
        a[0] = 0;
        *n = 1;
    }
}

void privedenie_arr(int *buff1, int *len1, int *buff2, int *len2) {
    if (*len1 >= *len2) {
        add_delete_zeros(buff1, len1, -1);
        add_delete_zeros(buff2, len2, *len2 - *len1);
    } else {
        add_delete_zeros(buff2, len2, -1);
        add_delete_zeros(buff1, len1, *len1 - *len2);
    }
}

void sum(int *buff1, int len1, int *buff2, int *result, int *result_length) {
    *result_length = len1;
    for (int i = 0; i < len1; i++) {
        result[i] = buff1[i] + buff2[i];
        if (result[i] >= 10) {
            result[i] = result[i] % 10;
            result[i - 1]++;
        }
    }
    add_delete_zeros(result, result_length, k_zeros(result, *result_length));
}
void sub(int *buff1, int len1, int *buff2, int *result, int *result_length) {
    *result_length = len1;
    int j1 = k_zeros(buff1, len1);
    int j2 = k_zeros(buff2, len1);
    if ((j1 > j2) || (j1 == j2 && buff1[j1] < buff2[j1]))
        *result_length = 0;
    else
        *result_length = len1;
    for (int i = len1 - 1; *result_length != 0 && i >= 0; i--) {
        result[i] = buff1[i] - buff2[i];
        if (result[i] < 0) {
            result[i] += 10;
            buff1[i - 1]--;
        }
    }
    if (*result_length != 0) add_delete_zeros(result, result_length, k_zeros(result, *result_length));
}
