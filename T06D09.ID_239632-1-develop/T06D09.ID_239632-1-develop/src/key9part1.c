/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);
int even_exist(int *buffer, int length);
/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX], res[NMAX], sum_even, res_n;
    if (input(data, &n) != -1) {
        if (even_exist(data, n)) {
            sum_even = sum_numbers(data, n);
            printf("%d\n", sum_even);
            res_n = find_numbers(data, n, sum_even, res);
            output(res, res_n);
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

int input(int *buffer, int *length) {
    int stop = 0;
    if (scanf("%d", length) == 1 && *length > 0 && *length <= NMAX) {
        for (int i = 0; i < *length && stop == 0; i++) {
            if (scanf("%d", &buffer[i]) != 1) stop = -1;
        }
    } else
        stop = -1;
    return stop;
}

void output(int *buffer, int length) {
    if (length <= 0)
        printf("n/a");
    else {
        for (int i = 0; i < length; i++) {
            printf("%d", buffer[i]);
            if (i != length - 1) printf(" ");
        }
    }
}
/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
        }
    }
    return sum;
}

int even_exist(int *buffer, int length) {
    int k = 0;
    for (int i = 0; i < length && k == 0; i++) {
        if (buffer[i] % 2 == 0) {
            k = 1;
        }
    }
    return k;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int n_numbers = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[n_numbers] = buffer[i];
            n_numbers++;
        }
    }
    return n_numbers;
}
